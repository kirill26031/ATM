#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H
#include "repository/transactionrepository.h"
#include "repository/cardrepository.h"
#include "util/utils.h"


class TransactionService
{
public:
    ~TransactionService(){}
    static TransactionService* getInstance()
    {
        if(_service == nullptr) _service = new TransactionService();
        return _service;
    }

    bool Transfer(long amount, long from_card_id, long to_card_id);
protected:
    TransactionService();
private:
    bool GetMoney(long amount, long from_card_id, long to_card_id, bool execute, bool dependant);
    bool AddMoney(long amount, long from_card_id, long to_card_id, bool execute, bool dependant);

    TransactionRepository* _transaction_rep;
    CardRepository* _card_rep;
    static TransactionService* _service;
};

#endif // TRANSACTIONSERVICE_H
