#ifndef AUTOMATICTRANSACTIONSERVICE_H
#define AUTOMATICTRANSACTIONSERVICE_H

#include "repository/automatictransactionrepository.h"
#include "repository/transactionrepository.h"
#include "repository/vector_impl/automatictransactionrepositoryvectorimpl.h"
#include "repository/vector_impl/transactionrepositoryvectorimpl.h"

class AutomaticTransactionService
{
public:
    ~AutomaticTransactionService(){}
    static AutomaticTransactionService* getInstance()
    {
        if(_service == nullptr) _service = new AutomaticTransactionService();
        return _service;
    }

protected:
    AutomaticTransactionService();

private:
    TransactionRepository* _transaction_rep;
    AutomaticTransactionRepository* _a_tr_rep;
    static AutomaticTransactionService* _service;
};

#endif // AUTOMATICTRANSACTIONSERVICE_H
