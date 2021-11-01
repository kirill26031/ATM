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
    virtual const CardEntity& getByCardId(std::array<int, 16> cardId) = 0;

protected:
    CardRepository() : Repository<CardEntity>() {}
    virtual ~CardRepository() {}
};

#endif // CARDREPOSITORY_H
