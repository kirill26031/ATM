#ifndef AUTOMATICTRANSACTIONREPOSITORY_H
#define AUTOMATICTRANSACTIONREPOSITORY_H

#include <model/automatictransactionentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class AutomaticTransactionRepository : public Repository<AutomaticTransactionEntity>
{
public:
    virtual ~AutomaticTransactionRepository() {}

protected:
    AutomaticTransactionRepository() : Repository<AutomaticTransactionEntity>() {}
};

#endif // AUTOMATICTRANSACTIONREPOSITORY_H
