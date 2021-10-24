#ifndef AUTOMATICTRANSACTIONENTITY_H
#define AUTOMATICTRANSACTIONENTITY_H

#include "entity.h"


class AutomaticTransactionEntity : public Entity
{
public:
    AutomaticTransactionEntity(long id, long from_card_id, long to_card_id, long amount, long part, double time_period);

    long from_card_id, to_card_id;
    long amount; //sumLimit in class diagram
    long part; //amount in class diagram
    double time_period; //distanceInDays in class diagram

};

#endif // AUTOMATICTRANSACTIONENTITY_H
