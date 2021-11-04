#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H

#include <model/transactionentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class TransactionRepository : public Repository<TransactionEntity>
{
//public:
protected:
    TransactionRepository() : Repository<TransactionEntity>() {}
    virtual ~TransactionRepository() {}
};

#endif // TRANSACTIONREPOSITORY_H
