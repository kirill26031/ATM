#include "userrepositoryvectorimpl.h"

UserRepository* UserRepositoryVectorImpl::_rep = nullptr;

UserRepositoryVectorImpl::UserRepositoryVectorImpl() : UserRepository() {}


const UserEntity& UserRepositoryVectorImpl::getById(long id)
{
    for(UserEntity& e : _entities)
    {
        if(e.id() == id) return e;
    }
    throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
}

const std::vector<UserEntity>& UserRepositoryVectorImpl::getAll()
{
    return _entities;
}

void UserRepositoryVectorImpl::setById(long id, UserEntity& user)
{
    for(UserEntity& e : _entities)
    {
        if(e.id() == id)
        {
            e = user;
            return;
        }
    }
    throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
}

void UserRepositoryVectorImpl::deleteById(long id)
{
    if(id >= 0 && id < _entities.size())
    {
        _entities.erase(_entities.begin()+id);
    }
    else throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
}

UserRepository* UserRepositoryVectorImpl::getInstance()
{
    if(_rep == nullptr) _rep = new UserRepositoryVectorImpl();
    return _rep;
}
