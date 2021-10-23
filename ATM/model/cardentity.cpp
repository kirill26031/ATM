#include "cardentity.h"

CardEntity::CardEntity(long id, std::array<int, 16> cardId, std::array<int, 4> pin, long userId, const std::string& name,
    long balance, long minBalance, long maxBalance, long* reserveCardId, long* overflowCardId) : Entity(id),
    _cardId(cardId), _pin(pin), _userId(userId), _name(name), _balance(balance), _minBalance(minBalance), _reserveCardId(reserveCardId), _overflowCardId(overflowCardId)
{

}
