#include "cardservice.h"

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
    try {
        const CardEntity& e = _card_rep->getByCardId(card_id);
        if(e.pin() == old_pin)
        {
            CardEntity newCard(e.id(), e.cardId(), new_pin, e.userId(), e.name(), e.balance(),
                               e.minBalance(), e.maxBalance(), e.reserveCardId(), e.overflowCardId());
            _card_rep->setById(e.id(), newCard);
        } else {
            throw new IncorrectCardAuthInfoException("Incorrect card authentication exception while trying to change pin");
        }
    }
    catch(const NotFoundException& nfe)
    {
        int x = 2+ 2;
    }
}




bool cardIdExists(long long card_id);
bool areCardCredentialsCorrect(long long card_id, int pin);
const CardEntity& generateCard(long user_id);
void setAsReserveCard(long long protected_card_id, long long reserve_card_id, long min_limit);
void setAsOverflowCard(long long from_card_id, long long from_to_id, long max_limit);
