#ifndef CARDSERVICE_H
#define CARDSERVICE_H

//#include "repository/vector_impl./cardrepositoryvectorimpl.h"
#include "repository/db_impl/cardrepositorydbimpl.h"
#include "exception/incorrectcardauthinfoexception.h"
#include "exception/circulardependancyexception.h"

class CardService
{
public:
    void editPin(long long card_id, int old_pin, int new_pin);
    bool cardIdExists(long long card_id);
    bool areCardCredentialsCorrect(long long card_id, int pin);
    long getCardIdByCredentials(long long card_id, int pin);
    long generateCard(long user_id, const std::string& name);
    CardEntity getCardById(long id);
    CardEntity getByCardNumber(long long card_number);
    void setAsReserveCard(long long protected_card_id, long long reserve_card_id, long min_limit);
    void setAsOverflowCard(long long from_card_id, long long to_card_id, long max_limit);

    static CardService* getInstance();
protected:
    CardService();
    ~CardService(){}
private:
    bool detectedCircularDependancy(long card_id, long other_id, bool is_reserve);

    CardRepository* _card_rep;
    static CardService* _service;
};

#endif // CARDSERVICE_H
