#ifndef NOT_FOUND_EXCEPTION
#define NOT_FOUND_EXCEPTION
#include "exception/notfoundexception.h"
#endif

#ifndef CARDREPOSITORYIMPL_H
#define CARDREPOSITORYIMPL_H

#include "cardrepository.h"

class CardRepositoryImpl : public CardRepository
{
public:
    CardRepositoryImpl();
    ~CardRepositoryImpl();

    const CardEntity& getById(long);
    const std::vector<CardEntity>& getAll();
    void setById(long, CardEntity&);
    void deleteById(long);
    const CardEntity& getByCardId(std::array<int, 16> cardId);
private:
    std::vector<CardEntity> _entities;
};

#endif // CARDREPOSITORYIMPL_H
