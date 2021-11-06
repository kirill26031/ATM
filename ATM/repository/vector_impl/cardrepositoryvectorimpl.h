#ifndef CARDREPOSITORYVECTORIMPL_H
#define CARDREPOSITORYVECTORIMPL_H

#include "exception/notfoundexception.h"
#include <string>
#include "repository/cardrepository.h"

class CardRepositoryVectorImpl : public CardRepository
{
public:
    const CardEntity& getById(long) override;
    const std::vector<CardEntity>& getAll() override;
    void setById(long, CardEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    const CardEntity& getByCardId(long long) override;
    const std::vector<CardEntity> getCardsDependantOnThisByReserve(long id) override;
    const std::vector<CardEntity> getCardsDependantOnThisByOverflow(long id) override;
    static CardRepository* getInstance();
protected:
    CardRepositoryVectorImpl();
    ~CardRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor
private:
    std::vector<CardEntity> _entities;
    static CardRepository* _rep;
};

#endif // CARDREPOSITORYVECTORIMPL_H
