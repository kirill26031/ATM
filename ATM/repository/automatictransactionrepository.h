#ifndef AUTOMATICTRANSACTIONREPOSITORY_H
#define AUTOMATICTRANSACTIONREPOSITORY_H

#include <model/automatictransactionentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class AutomaticTransactionRepository : Repository<AutomaticTransactionEntity>
{
public:
    AutomaticTransactionRepository();

    virtual const AutomaticTransactionEntity& getById(long id) override {
        for (AutomaticTransactionEntity& entity : _entities)
            if (entity._id == id)
                return entity;
        throw NotFoundException(std::string("AutomaticTransaction with id=")+std::to_string(id)+" not found in AutomaticTransactionRepository");
    }

    virtual void setById(long id, AutomaticTransactionEntity& new_entity) override {
        for (AutomaticTransactionEntity& entity : _entities)
            if (entity._id == id) {
                entity = new_entity;
                return;
            }
        throw NotFoundException(std::string("AutomaticTransaction with id=")+std::to_string(id)+" not found in AutomaticTransactionRepository");
    }

    virtual void deleteById(long id) override {
        for (int i = 0; i < _entities.size(); i++)
            if (_entities[i]._id == id) {
                _entities.erase(_entities.begin() + i);
                return;
            }
        throw NotFoundException(std::string("AutomaticTransaction with id=")+std::to_string(id)+" not found in AutomaticTransactionRepository");
    }
};

#endif // AUTOMATICTRANSACTIONREPOSITORY_H
