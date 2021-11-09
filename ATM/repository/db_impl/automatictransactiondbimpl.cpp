#include "automatictransactiondbimpl.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlError>
#include "exception/sqlexception.h"

AutomaticTransactionRepository* AutomaticTransactionRepositoryDBImpl::_rep = nullptr;

AutomaticTransactionRepositoryDBImpl::AutomaticTransactionRepositoryDBImpl() : AutomaticTransactionRepository(), _db_manager(DBManager::getInstance()) {}

AutomaticTransactionRepository* AutomaticTransactionRepositoryDBImpl::getInstance()
{
    if(_rep == nullptr) _rep = new AutomaticTransactionRepositoryDBImpl();
    return _rep;
}


AutomaticTransactionEntity AutomaticTransactionRepositoryDBImpl::getById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id, from_card_id, to_card_id, total, amount, part, time_period, last_executed_time, aborted FROM schema.automatic_transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    if(!query.next())
    {
        throw NotFoundException(std::string("AutomaticTransaction with id=").append(std::to_string(id)).append(" not found in AutomaticTransactionRepository"));
    }
    QSqlRecord record(query.record());
    AutomaticTransactionEntity automatic_transaction(record.value(0).toLongLong(), record.value(1).toLongLong(),
                                                     record.value(2).toLongLong(), record.value(3).toLongLong(),
                                                     record.value(4).toLongLong(), record.value(5).toLongLong(),
                                                     record.value(6).toLongLong(), record.value(7).toLongLong(),
                                                     record.value(8).toBool());
    return automatic_transaction;
}

std::vector<AutomaticTransactionEntity> AutomaticTransactionRepositoryDBImpl::getAll()
{
    QSqlQuery query("SELECT id, from_card_id, to_card_id, total, amount, part, time_period, last_executed_time, aborted FROM schema.automatic_transaction", _db_manager->db());
    std::vector<AutomaticTransactionEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        AutomaticTransactionEntity automatic_transaction(record.value(0).toLongLong(), record.value(1).toLongLong(),
                                                         record.value(2).toLongLong(), record.value(3).toLongLong(),
                                                         record.value(4).toLongLong(), record.value(5).toLongLong(),
                                                         record.value(6).toLongLong(), record.value(7).toLongLong(),
                                                         record.value(8).toBool());
        res.push_back(automatic_transaction);
    }
    return res;
}

void AutomaticTransactionRepositoryDBImpl::setById(long id, AutomaticTransactionEntity& automaticTransaction)
{
    QSqlQuery query(_db_manager->db());
    if(id == -1)
    {
        query.prepare(QString("INSERT INTO schema.automatic_transaction (from_card_id, to_card_id, total, amount, part, time_period, last_executed_time, aborted) ")+
                      QString("VALUES ( :from_card_id, :to_card_id, :total, :amount, :part, :time_period, :last_executed_time, :aborted )"));
    }
    else{
        query.prepare(QString("INSERT INTO schema.automatic_transaction (id, from_card_id, to_card_id, total, amount, part, time_period, last_executed_time, aborted) ")+
                      QString("VALUES ( :id, :from_card_id, :to_card_id, :total, :amount, :part, :time_period, :last_executed_time, :aborted )")+
                      QString(" ON CONFLICT (id) DO UPDATE SET name = excluded.name"));
        query.bindValue(":id", QVariant::fromValue(id));
    }
    query.bindValue(":from_card_id", QVariant::fromValue(automaticTransaction.fromCardId()));
    query.bindValue(":to_card_id", QVariant::fromValue(automaticTransaction.toCardId()));
    query.bindValue(":amount", QVariant::fromValue(automaticTransaction.amount()));

    if(!query.exec())
    {
//        auto r = query.executedQuery();
        throw SQLException(query.lastError().text().toStdString());
    }
}

void AutomaticTransactionRepositoryDBImpl::deleteById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("DELETE FROM schema.automatic_transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
}

bool AutomaticTransactionRepositoryDBImpl::existsById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id FROM schema.automatic_transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    return query.next();
}
