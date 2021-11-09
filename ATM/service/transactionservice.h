#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H
#include "repository/transactionrepository.h"
#include "repository/cardrepository.h"
#include "repository/vector_impl/transactionrepositoryvectorimpl.h"
#include "repository/vector_impl/cardrepositoryvectorimpl.h"
#include "util/utils.h"
//#include "automatictransactionservice.h"


class TransactionService
{
public:
    ~TransactionService(){}
    static TransactionService* getInstance()
    {
        if(_service == nullptr) _service = new TransactionService();
        return _service;
    }

    bool makeTransfer(long amount, long long from_card_n, long long to_card_n);

    bool Transfer(long amount, long from_card_id, long to_card_id, long* automatic_transaction_id = nullptr);

    std::vector<TransactionEntity> getSentTransactions(long sender_card_id);

    std::vector<TransactionEntity> getReceivedTransactions(long receiver_card_id);

    TransactionEntity getById(long id);
protected:
    TransactionService();
private:
    bool prepareTransferFromCard(long amount, long from_card_id, long to_card_id, bool execute, bool dependant);
    bool prepareTransferToCard(long amount, long from_card_id, long to_card_id, bool execute, bool dependant);


    TransactionRepository* _transaction_rep;
    CardRepository* _card_rep;
    static TransactionService* _service;
};

#endif // TRANSACTIONSERVICE_H
