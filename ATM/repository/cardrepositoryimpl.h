#ifndef NOT_FOUND_EXCEPTION
#define NOT_FOUND_EXCEPTION
#include "exception/notfoundexception.h"
#endif

#ifndef CARDREPOSITORYIMPL_H
#define CARDREPOSITORYIMPL_H

#include "cardrepository.h"

class CardRepositoryImpl : public CardRepository
{
private:
    CardRepositoryImpl();
    ~CardRepositoryImpl(){}
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

#endif // CARDREPOSITORYIMPL_H
