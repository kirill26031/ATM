#ifndef CARDREPOSITORYVECTORIMPL_H
#define CARDREPOSITORYVECTORIMPL_H

#include "exception/notfoundexception.h"
#include "repository/cardrepository.h"

class CardRepositoryVectorImpl : public CardRepository
{
private:
    CardRepositoryVectorImpl();
    ~CardRepositoryVectorImpl(){}
public:
    const CardEntity& getById(long) override;
    const std::vector<CardEntity>& getAll() override;
    void setById(long, CardEntity&) override;
    void deleteById(long) override;
    const CardEntity& getByCardId(std::array<int, 16> cardId) override;
    static CardRepository* getInstance();
private:
    std::vector<CardEntity> _entities;
    static CardRepository* _rep;
};

#endif // CARDREPOSITORYVECTORIMPL_H
