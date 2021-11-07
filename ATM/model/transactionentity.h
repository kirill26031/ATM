#ifndef TRANSACTIONENTITY_H
#define TRANSACTIONENTITY_H

#include "entity.h"
#include <ctime>

class TransactionEntity : public Entity
{
public:
    TransactionEntity(long id, long from_card_id, long to_card_id, long amount, int type, long* automatic_transaction_id = 0);
    TransactionEntity(const TransactionEntity& other);
    ~TransactionEntity();
    TransactionEntity& operator=(const TransactionEntity& other);

    const long& fromCardId() const {return _from_card_id;}
    const long& toCardId() const {return _to_card_id;}
    const long& amount() const {return _amount;}
    const int& type() const {return _type;}
    long* automaticTransactionId() const {return _automatic_transaction_id;}
private:
    long _from_card_id;
    long _to_card_id;
    long _amount;
//    time_t _time;
/*
    0 - one time transaction made by user
    1 - automatic transaction
    2 - transaction due to reserve card operation
    3 - transaction due to overflow card operation
*/
    int _type;
    long* _automatic_transaction_id;

};

#endif // TRANSACTIONENTITY_H
