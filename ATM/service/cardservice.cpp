#include "cardservice.h"
#include "util/utils.h"

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
    }  catch (const NotFoundException& e) {
        return false;
    }
    return true;
}

bool CardService::areCardCredentialsCorrect(long long card_id, int pin)
{
    const CardEntity& card = _card_rep->getByCardId(card_id);
    return card.pin() == pin;
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

void CardService::setAsReserveCard(long long protected_card_id, long long reserve_card_id, long min_limit)
{
//    if(cardIdExists(protected_card_id) && cardIdExists(reserve_card_id))
//    {

//    }
}

void CardService::setAsOverflowCard(long long from_card_id, long long from_to_id, long max_limit)
{

}
