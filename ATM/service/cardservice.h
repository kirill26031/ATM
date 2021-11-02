#ifndef CARDSERVICE_H
#define CARDSERVICE_H

#include "repository/vector_impl./cardrepositoryvectorimpl.h"
#include "exception/incorrectcardauthinfoexception.h"

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
