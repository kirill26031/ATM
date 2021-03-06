#ifndef CARDREPOSITORYVECTORIMPL_H
#define CARDREPOSITORYVECTORIMPL_H

#include "exception/notfoundexception.h"
#include <string>
#include "repository/cardrepository.h"

class CardRepositoryVectorImpl : public CardRepository
{
public:
    CardEntity getById(long) override;
    std::vector<CardEntity> getAll() override;
    void setById(long, const CardEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    void clearAll() override;
    CardEntity getByCardId(long long) override;
    std::vector<CardEntity> getCardsDependantOnThisByReserve(long id) override;
    std::vector<CardEntity> getCardsDependantOnThisByOverflow(long id) override;
    static CardRepository* getInstance();
    ~CardRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor

protected:
    CardRepositoryVectorImpl();
private:
    std::vector<CardEntity> _entities;
    static CardRepository* _rep;
};

#endif // CARDREPOSITORYVECTORIMPL_H
