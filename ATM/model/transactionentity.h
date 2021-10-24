#ifndef TRANSACTIONENTITY_H
#define TRANSACTIONENTITY_H

#include "entity.h"

class TransactionEntity : public Entity
{
public:
    TransactionEntity(long id, long from_card_id, long to_card_id, long amount);

    long from_card_id, to_card_id;
    long amount;

};

#endif // TRANSACTIONENTITY_H
