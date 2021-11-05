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
        long balance, unsigned long minBalance = 0, unsigned long maxBalance = ULONG_MAX, long* reserveCardId = 0, long* overflowCardId = 0);
    ~CardEntity();
    CardEntity& operator=(const CardEntity&);
    CardEntity(const CardEntity&);


    const long long& cardId() const {return _card_id;}
    const int& pin() const {return _pin;}
    const long& userId() const {return _user_id;}
    const std::string& name() const {return _name;}
    const long& balance() const {return _balance;}
    const unsigned long& minBalance() const {return _min_balance;}
    const unsigned long& maxBalance() const {return _max_balance;}
    long* reserveCardId() const {return _reserve_card_id;}
    long* overflowCardId() const {return _overflow_card_id;}

private:
    long long _card_id;
    int _pin;
    long _user_id;
    std::string _name;
    long _balance;
    unsigned long _min_balance;
    unsigned long _max_balance;
    long* _reserve_card_id;
    long* _overflow_card_id;


};

#endif // CARDENTITY_H
