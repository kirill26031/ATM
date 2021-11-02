#include "cardservice.h"

CardService::CardService() : _repository(CardRepositoryVectorImpl::getInstance())
{

}

void CardService::editPin(std::array<int, 16> cardId, std::array<int, 4> oldPin, std::array<int, 4> newPin)
{
    try {
        const CardEntity& e = _repository->getByCardId(cardId);
        if(e._pin == oldPin)
        {
            CardEntity newCard = e;
            newCard._pin = newPin;
            _repository->setById(e._id, newCard);
        } else {
            throw new IncorrectCardAuthInfoException("Incorrect card authentication exception while trying to change pin");
        }
    }
    catch(const NotFoundException& nfe)
    {
        int x = 2+ 2;
    }
}
