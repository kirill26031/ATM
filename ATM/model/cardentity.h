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
    ~CardEntity(){}
    CardEntity& operator=(const CardEntity&);
    CardEntity(const CardEntity&);

    long long _cardId;
    int _pin;
    long _userId;
    std::string _name;
    long _balance;
    long _minBalance;
    long _maxBalance;
    long* _reserveCardId;
    long* _overflowCardId;
private:

};

#endif // CARDENTITY_H
