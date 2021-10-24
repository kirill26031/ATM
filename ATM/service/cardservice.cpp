#include "cardservice.h"

CardService::CardService() : _repository(CardRepositoryImpl())
{

}

void CardService::editPin(std::array<int, 16> cardId, std::array<int, 4> oldPin, std::array<int, 4> newPin)
{
    try {
        const CardEntity& e = _repository.getByCardId(cardId);
        if(e._pin == oldPin)
        {

        } else {
            throw new IncorrectCardAuthInfoException("Incorrect card authentication exception for cardId=");
        }
    }
    catch(const NotFoundException& nfe)
    {
        int x = 2+ 2;
    }
}
