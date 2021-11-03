#include "cardentity.h"

CardEntity::CardEntity(long id, long long cardId, int pin, long userId, const std::string& name,
    long balance, long* minBalance, long* maxBalance, long* reserveCardId, long* overflowCardId) : Entity(id),
    _card_id(cardId), _pin(pin), _user_id(userId), _name(name), _balance(balance), _min_balance(minBalance), _max_balance(maxBalance), _reserve_card_id(reserveCardId), _overflow_card_id(overflowCardId)
{
    if(minBalance != nullptr) _min_balance = new long(*minBalance);
    if(maxBalance != nullptr) _max_balance = new long(*maxBalance);
    if(reserveCardId != nullptr) _reserve_card_id = new long(*reserveCardId);
    if(overflowCardId != nullptr) _overflow_card_id = new long(*overflowCardId);
}

CardEntity::~CardEntity()
{
    if(_reserve_card_id != nullptr) delete _reserve_card_id;
    if(_overflow_card_id != nullptr) delete _overflow_card_id;
    if(_min_balance != nullptr) delete _min_balance;
    if(_max_balance != nullptr) delete _max_balance;
}

CardEntity& CardEntity::operator=(const CardEntity& other)
{
    _card_id = other._card_id;
    _pin = other._pin;
    _user_id = other._user_id;
    _name = other._name;
    _balance = other._balance;
    _min_balance = other._min_balance;
    _max_balance = other._max_balance;
    _reserve_card_id = other._reserve_card_id;
    _overflow_card_id = other._overflow_card_id;
    Entity::operator=(other);
    return *this;
}

CardEntity::CardEntity(const CardEntity& o) : Entity(o) , _card_id(o._card_id), _pin(o._pin), _balance(o._balance),
    _min_balance(o._min_balance), _max_balance(o._max_balance), _reserve_card_id(o._reserve_card_id), _overflow_card_id(o._overflow_card_id),
    _user_id(o._user_id), _name(o._name)
{

}
