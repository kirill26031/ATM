#include "automatictransactiondbimpl.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlError>
#include "exception/sqlexception.h"

AutomaticTransactionRepository* AutomaticTransactionRepositoryDBImpl::_rep = nullptr;

AutomaticTransactionRepositoryDBImpl::AutomaticTransactionRepositoryDBImpl() :
    AutomaticTransactionRepository(), _db_manager(DBManager::getInstance()),
    _cache(AutomaticTransactionRepositoryVectorImpl::getInstance()), _cache_modified(true)
{
    getAll();
}

void AutomaticTransactionRepositoryDBImpl::fillCache(const std::vector<AutomaticTransactionEntity>& vector)
{
    for(const AutomaticTransactionEntity& e : vector)
    {
        _cache->setById(e.id(), e);
    }
}

AutomaticTransactionRepository* AutomaticTransactionRepositoryDBImpl::getInstance()
{
    if(_rep == nullptr) _rep = new AutomaticTransactionRepositoryDBImpl();
    return _rep;
}


AutomaticTransactionEntity AutomaticTransactionRepositoryDBImpl::getById(long id)
{
    // qDebug() << "\nAutomaticTransactionRepositoryDBImpl::getById " << _cache_modified;
    if(!_cache_modified) return _cache->getById(id);
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
    // qDebug() << "\nAutomaticTransactionRepositoryDBImpl::getAll " << _cache_modified;
    if(!_cache_modified) return _cache->getAll();
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
    fillCache(res);
    _cache_modified = false;
    return res;
}

void AutomaticTransactionRepositoryDBImpl::setById(long id, const AutomaticTransactionEntity& automaticTransaction)
{
    // qDebug() << "\nAutomaticTransactionRepositoryDBImpl::setById " << _cache_modified;
    _cache_modified = true;
    QSqlQuery query(_db_manager->db());
    if(id == -1)
    {
        query.prepare(QString("INSERT INTO schema.automatic_transaction (from_card_id, to_card_id, total, amount, part, time_period, last_executed_time, aborted) ")+
                      QString("VALUES ( :from_card_id, :to_card_id, :total, :amount, :part, :time_period, :last_executed_time, :aborted )"));
    }
    else{
        query.prepare(QString("UPDATE schema.automatic_transaction SET ")+
                      QString("( from_card_id, to_card_id, total, amount, part, time_period, last_executed_time, aborted) = ")+
                      QString("( :from_card_id, :to_card_id, :total, :amount, :part, :time_period, :last_executed_time, :aborted ) ")+
                      QString("WHERE id = :id"));
        query.bindValue(":id", QVariant::fromValue(id));
    }
    query.bindValue(":from_card_id", QVariant::fromValue(automaticTransaction.fromCardId()));
    query.bindValue(":to_card_id", QVariant::fromValue(automaticTransaction.toCardId()));
    query.bindValue(":total", QVariant::fromValue(automaticTransaction.total()));
    query.bindValue(":amount", QVariant::fromValue(automaticTransaction.amount()));
    query.bindValue(":part", QVariant::fromValue(automaticTransaction.part()));
    query.bindValue(":time_period", QVariant::fromValue(automaticTransaction.time_period()));
    query.bindValue(":last_executed_time", QVariant::fromValue(automaticTransaction.lastExecutedTime()));
    query.bindValue(":aborted", QVariant::fromValue(automaticTransaction.aborted()));

    if(!query.exec())
    {
//        auto r = query.executedQuery();
        throw SQLException(query.lastError().text().toStdString());
    }
}

void AutomaticTransactionRepositoryDBImpl::deleteById(long id)
{
    // qDebug() << "\nAutomaticTransactionRepositoryDBImpl::deleteById ";
    _cache->deleteById(id);
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
    // qDebug() << "\nAutomaticTransactionRepositoryDBImpl::existsById " << _cache_modified;
    if(!_cache_modified) return _cache->existsById(id);
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id FROM schema.automatic_transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    return query.next();
}
