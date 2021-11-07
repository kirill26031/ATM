#include "userrepositorydbimpl.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlField>
#include <QSqlRecord>

UserRepository* UserRepositoryDBImpl::_rep = nullptr;

UserRepositoryDBImpl::UserRepositoryDBImpl() : UserRepository(), _db_manager(DBManager::getInstance()) {}

UserRepository* UserRepositoryDBImpl::getInstance()
{
    if(_rep == nullptr) _rep = new UserRepositoryDBImpl();
    return _rep;
}


UserEntity UserRepositoryDBImpl::getById(long id)
{
    QSqlQuery query(_db_manager->db());
    query.prepare("SELECT * FROM user WHERE id=:id");
    query.bindValue(":id", QVariant::fromValue(id));
    query.exec();
    if(!query.next())
    {
        throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
    }
    QSqlRecord record(query.record());
    UserEntity user(record.value(record.indexOf("id")).toLongLong(), record.value(record.indexOf("name")).toString().toStdString());
    return user;
}

std::vector<UserEntity> UserRepositoryDBImpl::getAll()
{

}

void UserRepositoryDBImpl::setById(long id, UserEntity& user)
{

}

void UserRepositoryDBImpl::deleteById(long id)
{

}

bool UserRepositoryDBImpl::existsById(long id)
{

}
