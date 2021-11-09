#include "transactionrepositorydbimpl.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlError>
#include "exception/sqlexception.h"

TransactionRepository* TransactionRepositoryDBImpl::_rep = nullptr;

TransactionRepositoryDBImpl::TransactionRepositoryDBImpl() : TransactionRepository(), _db_manager(DBManager::getInstance()) {}

TransactionRepository* TransactionRepositoryDBImpl::getInstance()
{
    if(_rep == nullptr) _rep = new TransactionRepositoryDBImpl();
    return _rep;
}


TransactionEntity TransactionRepositoryDBImpl::getById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id, from_card_id, to_card_id, amount, type, automatic_transaction_id FROM schema.transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    if(!query.next())
    {
        throw NotFoundException(std::string("Transaction with id=").append(std::to_string(id)).append(" not found in TransactionRepository"));
    }
    QSqlRecord record(query.record());
    long* automatic_transaction_id = record.isNull(5) ? 0 : new long(record.value(5).toLongLong());
    TransactionEntity transaction(record.value(0).toLongLong(), record.value(1).toLongLong(), record.value(2).toLongLong(),
                                  record.value(3).toLongLong(), record.value(4).toInt(), automatic_transaction_id);
    return transaction;
}

std::vector<TransactionEntity> TransactionRepositoryDBImpl::getAll()
{
    QSqlQuery query("SELECT id, from_card_id, to_card_id, amount, type, automatic_transaction_id FROM schema.transaction", _db_manager->db());
    std::vector<TransactionEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        long* automatic_transaction_id = record.isNull(5) ? 0 : new long(record.value(5).toLongLong());
        TransactionEntity transaction(record.value(0).toLongLong(), record.value(1).toLongLong(), record.value(2).toLongLong(),
                                      record.value(3).toLongLong(), record.value(4).toInt(), automatic_transaction_id);
        res.push_back(transaction);
    }
    return res;
}

void TransactionRepositoryDBImpl::setById(long id, TransactionEntity& transaction)
{
    QSqlQuery query(_db_manager->db());
    if(id == -1)
    {
        query.prepare(QString("INSERT INTO schema.transaction (from_card_id, to_card_id, amount, type, automatic_transaction_id) ")+
                      QString("VALUES ( :from_card_id, :to_card_id, :amount, :type, :automatic_transaction_id )"));
    }
    else{
        query.prepare(QString("INSERT INTO schema.transaction (id, from_card_id, to_card_id, amount, type, automatic_transaction_id) ")+
                      QString("VALUES ( :id, :from_card_id, :to_card_id, :amount, :type, :automatic_transaction_id )")+
                      QString(" ON CONFLICT (id) DO UPDATE SET name = excluded.name"));
        query.bindValue(":id", QVariant::fromValue(id));
    }
    query.bindValue(":from_card_id", QVariant::fromValue(transaction.fromCardId()));
    query.bindValue(":to_card_id", QVariant::fromValue(transaction.toCardId()));
    query.bindValue(":amount", QVariant::fromValue(transaction.amount()));
    query.bindValue(":type", QVariant::fromValue(transaction.type()));
    query.bindValue(":automatic_transaction_id", transaction.automaticTransactionId() == nullptr ?
                        QString::fromStdString(std::string("null")) : QVariant::fromValue(transaction.automaticTransactionId()));
//    auto r1 = query.boundValues();
    if(!query.exec())
    {
//        auto r = query.executedQuery();
        throw SQLException(query.lastError().text().toStdString());
    }
}

void TransactionRepositoryDBImpl::deleteById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("DELETE FROM schema.transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
}

bool TransactionRepositoryDBImpl::existsById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id FROM schema.transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    return query.next();
}
