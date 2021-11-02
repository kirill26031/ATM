#ifndef CARDSERVICE_H
#define CARDSERVICE_H

#include "repository/vector_impl./cardrepositoryvectorimpl.h"
#include "exception/incorrectcardauthinfoexception.h"

class CardService
{
public:
    CardService();
    ~CardService(){}

    void editPin(long long cardId, int oldPin, int newPin);

private:
    CardRepository* _repository;
};

#endif // CARDSERVICE_H
