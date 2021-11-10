#ifndef CARDREPOSITORY_H
#define CARDREPOSITORY_H

#include "model/cardentity.h"
#include "repository.h"

class CardRepository : public Repository<CardEntity>
{
public:
    virtual CardEntity getByCardId(long long cardId) = 0;
    virtual std::vector<CardEntity> getCardsDependantOnThisByReserve(long id) = 0;
    virtual std::vector<CardEntity> getCardsDependantOnThisByOverflow(long id) = 0;
    virtual ~CardRepository() {}

protected:
    CardRepository() : Repository<CardEntity>() {}
};

#endif // CARDREPOSITORY_H
