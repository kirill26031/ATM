#ifndef AUTOMATICTRANSACTIONENTITY_H
#define AUTOMATICTRANSACTIONENTITY_H

#include "entity.h"


class AutomaticTransactionEntity : public Entity
{
public:
    AutomaticTransactionEntity(long id, long from_card_id, long to_card_id, long amount, long part, long time_period, long long start_time);

    const long& fromCardId() const {return _from_card_id;}
    const long& toCardId() const {return _to_card_id;}
    const long& amount() const {return _amount;}
    const long& part() const {return _part;}
    const long& time_period() const {return _time_period; }
    const long long& startTime() const {return _start_time; }

private:
    long _from_card_id;
    long _to_card_id;
    long _amount;
    long _part; //amount of money to pay per time
    long _time_period; // in seconds
    long long _start_time; // timestamp of first planned transaction
};

#endif // AUTOMATICTRANSACTIONENTITY_H
