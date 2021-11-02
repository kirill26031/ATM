#ifndef AUTOMATICTRANSACTIONENTITY_H
#define AUTOMATICTRANSACTIONENTITY_H

#include "entity.h"


class AutomaticTransactionEntity : public Entity
{
public:
    AutomaticTransactionEntity(long id, long from_card_id, long to_card_id, long amount, long part, double time_period);

    const long& fromCardId() const {return _from_card_id;}
    const long& toCardId() const {return _to_card_id;}
    const long& amount() const {return _amount;}
    const long& part() const {return _part;}
    const double& time_period() const {return _time_period;}

private:
    long _from_card_id;
    long _to_card_id;
    long _amount; //sumLimit in class diagram
    long _part; //amount in class diagram
    double _time_period; //distanceInDays in class diagram

};

#endif // AUTOMATICTRANSACTIONENTITY_H
