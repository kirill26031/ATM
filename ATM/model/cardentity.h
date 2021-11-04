#ifndef CARDENTITY_H
#define CARDENTITY_H
#ifndef CLIMITS
#define CLIMITS
#include <climits>
#endif
#ifndef ARRAY
#define ARRAY
#include <array>
#endif

#include "entity.h"

//mutable entity
class CardEntity : public Entity
{
public:
    CardEntity(long id, long long cardId, int pin, long userId, const std::string& name,
        long balance, long minBalance = 0, long maxBalance = LONG_MAX, long* reserveCardId = 0, long* overflowCardId = 0);
    ~CardEntity();
    CardEntity& operator=(const CardEntity&);
    CardEntity(const CardEntity&);

    long long& cardId()  {return _card_id;}
    int& pin()  {return _pin;}
    long& userId()  {return _user_id;}
    std::string& name()  {return _name;}
    long& balance()  {return _balance;}
    long& minBalance()  {return _min_balance;}
    long& maxBalance()  {return _max_balance;}
    long* reserveCardId() const {return _reserve_card_id;}
    long* overflowCardId() const {return _overflow_card_id;}

private:
    long long _card_id;
    int _pin;
    long _user_id;
    std::string _name;
    long _balance;
    long _min_balance;
    long _max_balance;
    long* _reserve_card_id;
    long* _overflow_card_id;


};

#endif // CARDENTITY_H
