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
        query.prepare(QString("INSERT INTO schema.card ( id, card_id, pin, user_id, name, balance, min_balance, max_balance, reserve_card_id, overflow_card_id) ")+
                      QString("VALUES ( :id, :card_id, :pin, :user_id, :name, :balance, :min_balance, :max_balance, :reserve_card_id, :overflow_card_id ) ")+
                      QString("ON CONFLICT (id) DO UPDATE SET card_id = excluded.card_id , pin = excluded.pin , user_id = excluded.user_id , name = excluded.name , balance = excluded.balance , min_balance = excluded.min_balance , max_balance = excluded.max_balance , reserve_card_id = excluded.reserve_card_id , overflow_card_id = excluded.overflow_card_id "));
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
                        QString::fromStdString(std::string("null")) : QVariant::fromValue(card.reserveCardId()));
    query.bindValue(":overflow_card_id", card.overflowCardId() == nullptr ?
                        QString::fromStdString(std::string("null")) : QVariant::fromValue(card.overflowCardId()));
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
