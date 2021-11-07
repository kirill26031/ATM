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
    query.prepare("SELECT id, from_card_id, to_card_id, amount, type, automatic_transaction_id FROM schema.transaction WHERE id=:id");
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
    TransactionEntity transaction(record.value(0).toLongLong(), record.value(1).toLongLong(), record.value(2).toLongLong(),
                                  record.value(3).toLongLong(), record.value(4).toInt());
    return transaction;
}

std::vector<TransactionEntity> TransactionRepositoryDBImpl::getAll()
{
    QSqlQuery query("SELECT id, name FROM schema.Transaction", _db_manager->db());
    std::vector<TransactionEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        TransactionEntity Transaction(record.value(0).toLongLong(), record.value(1).toString().toStdString());
        res.push_back(Transaction);
    }
    return res;
}

void TransactionRepositoryDBImpl::setById(long id, TransactionEntity& Transaction)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("INSERT INTO schema.Transaction (id, name) VALUES (:id, :name ) ON CONFLICT (id) DO UPDATE SET name = excluded.name");
    query.bindValue(":id", QVariant::fromValue(id));
    query.bindValue(":name", QString::fromStdString(Transaction.name()));
    auto r1 = query.boundValues();
    if(!query.exec())
    {
        auto r = query.executedQuery();
        throw SQLException(query.lastError().text().toStdString());
    }
}

void TransactionRepositoryDBImpl::deleteById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("DELETE FROM schema.Transaction WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
}

bool TransactionRepositoryDBImpl::existsById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id, name FROM schema.Transaction WHERE id=:id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    return query.next();
}
