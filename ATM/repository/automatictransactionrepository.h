#ifndef AUTOMATICTRANSACTIONREPOSITORY_H
#define AUTOMATICTRANSACTIONREPOSITORY_H

#include <model/automatictransactionentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class AutomaticTransactionRepository : Repository<AutomaticTransactionEntity>
{
//public:
protected:
    AutomaticTransactionRepository() : Repository<AutomaticTransactionEntity>() {}
    virtual ~AutomaticTransactionRepository() {}
};

#endif // AUTOMATICTRANSACTIONREPOSITORY_H
