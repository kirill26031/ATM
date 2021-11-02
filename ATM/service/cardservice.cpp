#include "cardservice.h"

CardService* CardService::_service = nullptr;

CardService::CardService() : _cardRep(CardRepositoryVectorImpl::getInstance())
{

}

void CardService::editPin(long long cardId, int oldPin, int newPin)
{
    try {
        const CardEntity& e = _cardRep->getByCardId(cardId);
        if(e.pin() == oldPin)
        {
            CardEntity newCard(e.id(), e.cardId(), e.pin(), e.userId(), e.name(), e.balance(),
                               e.minBalance(), e.maxBalance(), e.reserveCardId(), e.overflowCardId());
            _cardRep->setById(e.id(), newCard);
        } else {
            throw new IncorrectCardAuthInfoException("Incorrect card authentication exception while trying to change pin");
        }
    }
    catch(const NotFoundException& nfe)
    {
        int x = 2+ 2;
    }
}

CardService* CardService::getInstance()
{
    if(_service == nullptr) _service = new CardService();
    return _service;
}
