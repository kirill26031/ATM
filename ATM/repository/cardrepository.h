#ifndef CARD_ENTITY
#define CARD_ENTITY
#include "model/cardentity.h"
#endif

#ifndef CARDREPOSITORY_H
#define CARDREPOSITORY_H

#include "repository.h"

class CardRepository : public Repository<CardEntity>
{
public:
    CardRepository() : Repository() {}
    ~CardRepository() = 0;

    virtual CardEntity getByCardId(std::array<int, 16> cardId);
};

#endif // CARDREPOSITORY_H
