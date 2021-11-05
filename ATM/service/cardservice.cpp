#include "cardservice.h"
#include "util/utils.h"
#include "exception/logicconflictexception.h"

CardService* CardService::_service = nullptr;

CardService::CardService() : _card_rep(CardRepositoryVectorImpl::getInstance())
{

}

CardService* CardService::getInstance()
{
    if(_service == nullptr) _service = new CardService();
    return _service;
}

void CardService::editPin(long long card_id, int old_pin, int new_pin)
{
    const CardEntity& e = _card_rep->getByCardId(card_id);
    if(e.pin() == old_pin)
    {
        CardEntity newCard(e.id(), e.cardId(), new_pin, e.userId(), e.name(), e.balance(),
            e.minBalance(), e.maxBalance(), e.reserveCardId(), e.overflowCardId());
        _card_rep->setById(e.id(), newCard);
     } else {
        throw IncorrectCardAuthInfoException("Incorrect card authentication exception while trying to change pin");
     }
}

bool CardService::cardIdExists(long long card_id)
{
    try {
        const CardEntity& card = _card_rep->getByCardId(card_id);
        return true;
    }  catch (const NotFoundException& e) {
        return false;
    }

}

bool CardService::areCardCredentialsCorrect(long long card_id, int pin)
{
    try {
        const CardEntity& card = _card_rep->getByCardId(card_id);
        return card.pin() == pin;
    }  catch (const NotFoundException e) {
        return false;
    }

}

long CardService::getCardIdByCredentials(long long card_id, int pin)
{
    const CardEntity& card = _card_rep->getByCardId(card_id);
    if(card.pin() == pin)
    {
        return card.id();
    }
    else{
        throw IncorrectCardAuthInfoException("Incorrect card authentication exception while trying to get card id");
    }
}

long CardService::generateCard(long user_id, const std::string& name)
{
    CardEntity card(generateId(), generateCardId(), generatePin(), user_id, name, 0);
    _card_rep->setById(card.id(), card);
    return card.id();
}

const CardEntity& CardService::getCardById(long id)
{
    return _card_rep->getById(id);
}

void CardService::setAsReserveCard(long long protected_card_id, long long reserve_card_id, unsigned long min_limit)
{
    if(cardIdExists(protected_card_id) && cardIdExists(reserve_card_id))
    {
        const CardEntity& pr = _card_rep->getByCardId(protected_card_id);
        const CardEntity& reserve = _card_rep->getByCardId(reserve_card_id);
        if(pr.balance() <= min_limit) throw LogicConflictException("You can't set minimum limit below it's current balance");
        CardEntity updated_protected_card(pr.id(), pr.cardId(), pr.pin(), pr.userId(), pr.name(), pr.balance(),
                                          min_limit, pr.maxBalance(), new long(reserve.id()));
        _card_rep->setById(pr.id(), updated_protected_card);
    }
    else
    {
        throw NotFoundException("One of card numbers provided to CardService::setAsReserveCard was incorrect");
    }
}

void CardService::setAsOverflowCard(long long from_card_id, long long to_card_id, unsigned long max_limit)
{
    if(cardIdExists(from_card_id) && cardIdExists(to_card_id))
    {
        const CardEntity& ov = _card_rep->getByCardId(from_card_id);
        const CardEntity& target = _card_rep->getByCardId(to_card_id);
        if(ov.balance() >= max_limit) throw LogicConflictException("You can't set maximum limit above it's current balance");
        CardEntity target_card(ov.id(), ov.cardId(), ov.pin(), ov.userId(), ov.name(), ov.balance(),
                               ov.minBalance(), max_limit, ov.reserveCardId(),
                               new long(target.id()));
        _card_rep->setById(target_card.id(), target_card);
    }
    else
    {
        throw NotFoundException("One of card numbers provided to CardService::setAsReserveCard was incorrect");
    }
}
