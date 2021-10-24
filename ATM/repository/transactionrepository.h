#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H

#include <model/transactionentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class TransactionRepository : Repository<TransactionEntity>
{
public:
    TransactionRepository();


    virtual const TransactionEntity& getById(long id) override {
        for (TransactionEntity& entity : _entities)
            if (entity._id == id)
                return entity;
        throw NotFoundException(std::string("Transaction with id=")+std::to_string(id)+" not found in TransactionRepository");
    }

    virtual void setById(long id, TransactionEntity& new_entity) override {
        for (TransactionEntity& entity : _entities)
            if (entity._id == id) {
                entity = new_entity;
                return;
            }
        throw NotFoundException(std::string("Transaction with id=")+std::to_string(id)+" not found in TransactionRepository");
    }

    virtual void deleteById(long id) override {
        for (int i = 0; i < _entities.size(); i++)
            if (_entities[i]._id == id) {
                _entities.erase(_entities.begin() + i);
                return;
            }
        throw NotFoundException(std::string("Transaction with id=")+std::to_string(id)+" not found in TransactionRepository");
    }

};

#endif // TRANSACTIONREPOSITORY_H
