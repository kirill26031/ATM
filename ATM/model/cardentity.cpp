#include "cardentity.h"

CardEntity::CardEntity(long id, std::array<int, 16> cardId, std::array<int, 4> pin, long userId, const std::string& name,
    long balance, long minBalance, long maxBalance, long* reserveCardId, long* overflowCardId) : Entity(id),
    _cardId(cardId), _pin(pin), _userId(userId), _name(name), _balance(balance), _minBalance(minBalance), _reserveCardId(reserveCardId), _overflowCardId(overflowCardId)
{

}

CardEntity& CardEntity::operator=(const CardEntity& other)
{
    _cardId = other._cardId;
    _pin = other._pin;
    _userId = other._userId;
    _name = other._name;
    _balance = other._balance;
    _minBalance = other._minBalance;
    _maxBalance = other._maxBalance;
    _reserveCardId = other._reserveCardId;
    _overflowCardId = other._overflowCardId;
    Entity::operator=(other);
    return *this;
}

CardEntity::CardEntity(const CardEntity& o) : Entity(o) , _cardId(o._cardId), _pin(o._pin), _balance(o._balance),
    _minBalance(o._minBalance), _maxBalance(o._maxBalance), _reserveCardId(o._reserveCardId), _overflowCardId(o._overflowCardId),
    _userId(o._userId), _name(o._name)
{

}
