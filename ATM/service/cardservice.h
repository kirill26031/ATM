#ifndef CARDSERVICE_H
#define CARDSERVICE_H

#include "repository/vector_impl./cardrepositoryvectorimpl.h"
#include "exception/incorrectcardauthinfoexception.h"

class CardService
{
public:
    void editPin(long long card_id, int old_pin, int new_pin);
    bool cardIdExists(long long card_id);
    bool areCardCredentialsCorrect(long long card_id, int pin);
    const CardEntity& generateCard(long user_id);
    void setAsReserveCard(long long protected_card_id, long long reserve_card_id, long min_limit);
    void setAsOverflowCard(long long from_card_id, long long from_to_id, long max_limit);

    static CardService* getInstance();
protected:
    CardService();
    ~CardService(){}
private:
    CardRepository* _card_rep;
    static CardService* _service;
};

#endif // CARDSERVICE_H
