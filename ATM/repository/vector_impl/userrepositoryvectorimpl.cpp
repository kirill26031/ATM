#include "userrepositoryvectorimpl.h"

UserRepository* UserRepositoryVectorImpl::_rep = nullptr;

UserRepositoryVectorImpl::UserRepositoryVectorImpl() : UserRepository() {
//    _entities.push_back(UserEntity(0, "Bill Crapet 0"));
//    _entities.push_back(UserEntity(1, "Bill Crapet 1"));
//    _entities.push_back(UserEntity(2, "Bill Crapet 2"));
}


UserEntity UserRepositoryVectorImpl::getById(long id)
{
    for(UserEntity& e : _entities)
    {
        if(e.id() == id) return e;
    }
    throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
}

std::vector<UserEntity> UserRepositoryVectorImpl::getAll()
{
    return _entities;
}

void UserRepositoryVectorImpl::setById(long id, const UserEntity& user)
{
    for(UserEntity& e : _entities)
    {
        if(e.id() == id)
        {
            e = user;
            return;
        }
    }

    _entities.push_back(user);

    //throw NotFoundException(std::string("User with id=").append(std::to_string(id)).append(" not found in UserRepository"));
}

void UserRepositoryVectorImpl::deleteById(long id)
{
    for(auto iter = _entities.begin(); iter != _entities.end(); ++iter)
    {
        if(iter->id() == id){
            _entities.erase(iter);
            break;
        }
    }
}

UserRepository* UserRepositoryVectorImpl::getInstance()
{
    if(_rep == nullptr) _rep = new UserRepositoryVectorImpl();
    return _rep;
}

bool UserRepositoryVectorImpl::existsById(long id)
{
    for(UserEntity& e : _entities)
    {
        if(e.id() == id) return true;
    }
    return false;
}
