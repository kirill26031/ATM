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
    CardEntity(long id, std::array<int, 16> cardId, std::array<int, 4> pin, long userId, const std::string& name,
        long balance, long minBalance = 0, long maxBalance = LONG_MAX, long* reserveCardId = 0, long* overflowCardId = 0);
    ~CardEntity(){}

    std::array<int, 16> _cardId;
    std::array<int, 4> _pin;
    long _userId;
    std::string _name;
    long _balance;
    long _minBalance;
    long _maxBalance;
    long* _reserveCardId;
    long* _overflowCardId;
private:
    CardEntity(const CardEntity&) = delete;
    void operator=(const CardEntity&) = delete;
};

#endif // CARDENTITY_H
