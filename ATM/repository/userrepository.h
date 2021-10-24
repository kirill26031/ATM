#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <model/userentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class UserRepository : public Repository<UserEntity>
{
public:
    virtual const UserEntity& getById(long id) override {
        for (UserEntity& entity : _entities)
            if (entity._id == id)
                return entity;
        throw NotFoundException(std::string("User with id=")+std::to_string(id)+" not found in UserRepository");
    }

    virtual void setById(long id, UserEntity& new_entity) override {
        for (UserEntity& entity : _entities)
            if (entity._id == id) {
                entity = new_entity;
                return;
            }
        throw NotFoundException(std::string("User with id=")+std::to_string(id)+" not found in UserRepository");
    }

    virtual void deleteById(long id) override {
        for (int i = 0; i < _entities.size(); i++)
            if (_entities[i]._id == id) {
                _entities.erase(_entities.begin() + i);
                return;
            }
        throw NotFoundException(std::string("User with id=")+std::to_string(id)+" not found in UserRepository");
    }

};

#endif // USERREPOSITORY_H
