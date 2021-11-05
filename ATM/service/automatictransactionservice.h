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

    long createAutomaticTransaction(long long from_card_n, long long to_card_n, long amount, long time_period, long start_time);
    void deleteAutomaticTransaction(long auto_tr_id);
    std::vector<AutomaticTransactionEntity> getAllAutomaticTransactionsFromMe(long sender_card_id);
    std::vector<AutomaticTransactionEntity> getAllAutomaticTransactionsToMe(long receiver_card_id);
    void checkAndExecute();

protected:
    AutomaticTransactionService();

private:
    TransactionRepository* _transaction_rep;
    AutomaticTransactionRepository* _a_tr_rep;
    static AutomaticTransactionService* _service;
};

#endif // AUTOMATICTRANSACTIONSERVICE_H
