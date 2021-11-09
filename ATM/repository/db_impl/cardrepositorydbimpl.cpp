#include "cardrepositorydbimpl.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlError>
#include "exception/sqlexception.h"
#include "util/utils.h"

CardRepository* CardRepositoryDBImpl::_rep = nullptr;

CardRepositoryDBImpl::CardRepositoryDBImpl() : CardRepository(), _db_manager(DBManager::getInstance()) {}

CardRepository* CardRepositoryDBImpl::getInstance()
{
    if(_rep == nullptr) _rep = new CardRepositoryDBImpl();
    return _rep;
}


CardEntity CardRepositoryDBImpl::getById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id, card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id FROM schema.card WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    if(!query.next())
    {
        throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
    }
    QSqlRecord record(query.record());
    long* reserve_card_id = record.isNull(8) ? nullptr : new long(record.value(8).toLongLong());
    long* overflow_card_id = record.isNull(9) ? nullptr : new long(record.value(9).toLongLong());
    CardEntity card(record.value(0).toLongLong(), readCardNumber(record.value(1).toString().toStdString()),
                    readPin(record.value(2).toString().toStdString()), record.value(3).toLongLong(), record.value(4).toString().toStdString(),
                    record.value(5).toLongLong(), record.value(6).toLongLong(), record.value(7).toLongLong(), reserve_card_id, overflow_card_id);
    return card;
}

std::vector<CardEntity> CardRepositoryDBImpl::getAll()
{
    QSqlQuery query("SELECT id, card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id FROM schema.card", _db_manager->db());
    std::vector<CardEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        long* reserve_card_id = record.isNull(8) ? nullptr : new long(record.value(8).toLongLong());
        long* overflow_card_id = record.isNull(9) ? nullptr : new long(record.value(9).toLongLong());
        CardEntity card(record.value(0).toLongLong(), readCardNumber(record.value(1).toString().toStdString()),
                        readPin(record.value(2).toString().toStdString()), record.value(3).toLongLong(), record.value(4).toString().toStdString(),
                        record.value(5).toLongLong(), record.value(6).toLongLong(), record.value(7).toLongLong(), reserve_card_id, overflow_card_id);
        res.push_back(card);
    }
    return res;
}

void CardRepositoryDBImpl::setById(long id, CardEntity& card)
{
    QSqlQuery query(_db_manager->db());
    if(id == -1)
    {
        query.prepare(QString("INSERT INTO schema.card (card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id) VALUES ")+
                      QString("( :card_id, :pin, :user_id, :name, :balance, :min_balance, :max_balance, :reserve_card_id, :overflow_card_id )"));
    }
    else{
        query.prepare(QString("UPDATE schema.card SET ")+
                      QString("(card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id) = ")+
                      QString("( :card_id, :pin, :user_id, :name, :balance, :min_balance, :max_balance, :reserve_card_id, :overflow_card_id ) ")+
                      QString("WHERE id = :id"));
        query.bindValue(":id", QVariant::fromValue(id));
    }
    query.bindValue(":id", QVariant::fromValue(card.id()));
    query.bindValue(":card_id", QString::fromStdString(printCardNumber(card.cardId())));
    query.bindValue(":pin", QString::fromStdString(printPin(card.pin())));
    query.bindValue(":user_id", QVariant::fromValue(card.userId()));
    query.bindValue(":name", QString::fromStdString(card.name()));
    query.bindValue(":balance", QVariant::fromValue(card.balance()));
    query.bindValue(":min_balance", QVariant::fromValue(card.minBalance()));
    query.bindValue(":max_balance", QVariant::fromValue(card.maxBalance()));
    query.bindValue(":reserve_card_id", card.reserveCardId() == nullptr ?
                        QVariant::fromValue(nullptr) : QVariant::fromValue(*card.reserveCardId()));
    query.bindValue(":overflow_card_id", card.overflowCardId() == nullptr ?
                        QVariant::fromValue(nullptr) : QVariant::fromValue(*card.overflowCardId()));
//    auto b = query.boundValues();
//    for(auto i : b)
//    {
//        qDebug() << "\n" << i;
//    }
    if(!query.exec())
    {
//        auto r = query.executedQuery();
        throw SQLException(query.lastError().text().toStdString());
    }
}

void CardRepositoryDBImpl::deleteById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("DELETE FROM schema.card WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
}

bool CardRepositoryDBImpl::existsById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id FROM schema.card WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    return query.next();
}

CardEntity CardRepositoryDBImpl::getByCardId(long long cardId)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id, card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id FROM schema.card WHERE card_id = :card_id ");
    std::string card_numbers = printCardNumber(cardId);
    query.bindValue(":card_id", QString::fromStdString(card_numbers));
    if(!query.exec())
    {
        auto r = query.boundValues();
        for(auto i: r){
            qDebug() << "\n" << i;
        }
        auto r2 = query.lastQuery();

        throw SQLException(query.lastError().text().toStdString());
    }
    if(!query.next())
    {
        throw NotFoundException(std::string("Card with card_id=").append(std::to_string(cardId)).append(" not found in CardRepository"));
    }
    QSqlRecord record(query.record());
    long* reserve_card_id = record.isNull(8) ? nullptr : new long(record.value(8).toLongLong());
    long* overflow_card_id = record.isNull(9) ? nullptr : new long(record.value(9).toLongLong());
    CardEntity card(record.value(0).toLongLong(), readCardNumber(record.value(1).toString().toStdString()),
                    readPin(record.value(2).toString().toStdString()), record.value(3).toLongLong(), record.value(4).toString().toStdString(),
                    record.value(5).toLongLong(), record.value(6).toLongLong(), record.value(7).toLongLong(), reserve_card_id, overflow_card_id);
    return card;
}

std::vector<CardEntity> CardRepositoryDBImpl::getCardsDependantOnThisByReserve(long id)
{
    QSqlQuery query(QString("SELECT id, card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id FROM schema.card ")+
                    QString("WHERE reserve_card_id = :reserve_card_id "), _db_manager->db());
    query.bindValue(":reserve_card_id", QVariant::fromValue(id));
    std::vector<CardEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        long* reserve_card_id = record.isNull(8) ? nullptr : new long(record.value(8).toLongLong());
        long* overflow_card_id = record.isNull(9) ? nullptr : new long(record.value(9).toLongLong());
        CardEntity card(record.value(0).toLongLong(), readCardNumber(record.value(1).toString().toStdString()),
                        readPin(record.value(2).toString().toStdString()), record.value(3).toLongLong(), record.value(4).toString().toStdString(),
                        record.value(5).toLongLong(), record.value(6).toLongLong(), record.value(7).toLongLong(), reserve_card_id, overflow_card_id);
        res.push_back(card);
    }
    return res;
}

std::vector<CardEntity> CardRepositoryDBImpl::getCardsDependantOnThisByOverflow(long id)
{
    QSqlQuery query(QString("SELECT id, card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id FROM schema.card ")+
                    QString("WHERE overflow_card_id = :overflow_card_id "), _db_manager->db());
    query.bindValue(":overflow_card_id", QVariant::fromValue(id));
    std::vector<CardEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        long* reserve_card_id = record.isNull(8) ? nullptr : new long(record.value(8).toLongLong());
        long* overflow_card_id = record.isNull(9) ? nullptr : new long(record.value(9).toLongLong());
        CardEntity card(record.value(0).toLongLong(), readCardNumber(record.value(1).toString().toStdString()),
                        readPin(record.value(2).toString().toStdString()), record.value(3).toLongLong(), record.value(4).toString().toStdString(),
                        record.value(5).toLongLong(), record.value(6).toLongLong(), record.value(7).toLongLong(), reserve_card_id, overflow_card_id);
        res.push_back(card);
    }
    return res;
}
