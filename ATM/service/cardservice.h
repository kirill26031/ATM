#ifndef CARD_REPOSITORY_IMPL
#define CARD_REPOSITORY_IMPL
#include "repository/cardrepositoryimpl.h"
#endif
#ifndef INCORRECT_CARD_AUTH_EXCEPTION
#define INCORRECT_CARD_AUTH_EXCEPTION
#include "exception/incorrectcardauthinfoexception.h"
#endif

#ifndef CARDSERVICE_H
#define CARDSERVICE_H

class CardService
{
public:
    CardService();
    ~CardService(){}

    void editPin(std::array<int, 16> cardId, std::array<int, 4> oldPin, std::array<int, 4> newPin);

private:
    CardRepository* _repository;
};

#endif // CARDSERVICE_H
