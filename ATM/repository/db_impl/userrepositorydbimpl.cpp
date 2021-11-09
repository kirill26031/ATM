#include "userrepositorydbimpl.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlError>
#include "exception/sqlexception.h"

UserRepository* UserRepositoryDBImpl::_rep = nullptr;

UserRepositoryDBImpl::UserRepositoryDBImpl() : UserRepository(), _db_manager(DBManager::getInstance()),
    _cache(UserRepositoryVectorImpl::getInstance()), _cache_modified(true)
{
    getAll();
}

void UserRepositoryDBImpl::fillCache(const std::vector<UserEntity> &vector)
{
    for(const UserEntity& e : vector)
    {
        _cache->setById(e.id(), e);
    }
}

UserRepository* UserRepositoryDBImpl::getInstance()
{
    if(_rep == nullptr) _rep = new UserRepositoryDBImpl();
    return _rep;
}


UserEntity UserRepositoryDBImpl::getById(long id)
{
    // qDebug() << "\nUserRepositoryDBImpl::getById " << _cache_modified;
    if(!_cache_modified) return _cache->getById(id);
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id, name FROM schema.user WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    if(!query.next())
    {
        throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
    }
    QSqlRecord record(query.record());
    UserEntity user(record.value(0).toLongLong(), record.value(1).toString().toStdString());
    return user;
}

std::vector<UserEntity> UserRepositoryDBImpl::getAll()
{
    // qDebug() << "\nUserRepositoryDBImpl::getAll " << _cache_modified;
    if(!_cache_modified) return _cache->getAll();
    QSqlQuery query("SELECT id, name FROM schema.user", _db_manager->db());
    std::vector<UserEntity> res;
    while(query.next())
    {
        QSqlRecord record(query.record());
        UserEntity user(record.value(0).toLongLong(), record.value(1).toString().toStdString());
        res.push_back(user);
    }
    fillCache(res);
    _cache_modified = false;
    return res;
}

void UserRepositoryDBImpl::setById(long id, const UserEntity& user)
{
    // qDebug() << "\nUserRepositoryDBImpl::setById " << _cache_modified;
    _cache_modified = true;
    QSqlQuery query(_db_manager->db());
    if(id == -1)
    {
        query.prepare("INSERT INTO schema.user ( name) VALUES ( :name )");
    }
    else{
        query.prepare("UPDATE schema.user ( name) = ( :name ) WHERE id = :id");
        query.bindValue(":id", QVariant::fromValue(id));
    }
    query.bindValue(":name", QString::fromStdString(user.name()));
//    auto r1 = query.boundValues();
    if(!query.exec())
    {
//        auto r = query.executedQuery();
        throw SQLException(query.lastError().text().toStdString());
    }
}

void UserRepositoryDBImpl::deleteById(long id)
{
    // qDebug() << "\nUserRepositoryDBImpl::deleteById ";
    _cache->deleteById(id);
    QSqlQuery query(_db_manager->db());
    query.prepare("DELETE FROM schema.user WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
}

bool UserRepositoryDBImpl::existsById(long id)
{
    // qDebug() << "\nUserRepositoryDBImpl::existsById " << _cache_modified;
    if(!_cache_modified) return _cache->existsById(id);
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT id FROM schema.user WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if(!query.exec())
    {
        throw SQLException(query.lastError().text().toStdString());
    }
    return query.next();
}
