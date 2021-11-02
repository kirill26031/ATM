#ifndef CARDREPOSITORY_H
#define CARDREPOSITORY_H

#include "model/cardentity.h"
#include "repository.h"

class CardRepository : public Repository<CardEntity>
{
public:
    virtual const CardEntity& getByCardId(long long cardId) = 0;

protected:
    CardRepository() : Repository<CardEntity>() {}
    virtual ~CardRepository() {}
};

#endif // CARDREPOSITORY_H
