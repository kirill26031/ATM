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

class CardEntity : public Entity
{
public:
    CardEntity(long id, long long cardId, int pin, long userId, const std::string& name,
        long balance, long minBalance = 0, long maxBalance = LONG_MAX, long* reserveCardId = 0, long* overflowCardId = 0);
    ~CardEntity();
    CardEntity& operator=(const CardEntity&);
    CardEntity(const CardEntity&);

    const long long& cardId() const {return _cardId;}
    const int& pin() const {return _pin;}
    const long& userId() const {return _userId;}
    const std::string& name() const {return _name;}
    const long& balance() const {return _balance;}
    const long& minBalance() const {return _minBalance;}
    const long& maxBalance() const {return _maxBalance;}
    long* reserveCardId() const {return _reserveCardId;}
    long* overflowCardId() const {return _overflowCardId;}

private:
    long long _cardId;
    int _pin;
    long _userId;
    std::string _name;
    long _balance;
    long _minBalance;
    long _maxBalance;
    long* _reserveCardId;
    long* _overflowCardId;


};

#endif // CARDENTITY_H
