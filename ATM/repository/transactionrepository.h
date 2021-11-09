#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H

#include <model/transactionentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class TransactionRepository : public Repository<TransactionEntity>
{
public:
    virtual ~TransactionRepository() {}

protected:
    TransactionRepository() : Repository<TransactionEntity>() {}
};

#endif // TRANSACTIONREPOSITORY_H
