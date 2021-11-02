#ifndef TRANSACTIONENTITY_H
#define TRANSACTIONENTITY_H

#include "entity.h"

class TransactionEntity : public Entity
{
public:
    TransactionEntity(long id, long from_card_id, long to_card_id, long amount);

    const long& fromCardId() const {return _from_card_id;}
    const long& toCardId() const {return _to_card_id;}
    const long& amount() const {return _amount;}
private:
    long _from_card_id;
    long _to_card_id;
    long _amount;

};

#endif // TRANSACTIONENTITY_H
