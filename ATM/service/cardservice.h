#ifndef CARDSERVICE_H
#define CARDSERVICE_H

#include "repository/vector_impl./cardrepositoryvectorimpl.h"
#include "exception/incorrectcardauthinfoexception.h"

class CardService
{
public:
    void editPin(long long cardId, int oldPin, int newPin);
    static CardService* getInstance();
protected:
    CardService();
    ~CardService(){}
private:
    CardRepository* _card_rep;
    static CardService* _service;
};

#endif // CARDSERVICE_H
