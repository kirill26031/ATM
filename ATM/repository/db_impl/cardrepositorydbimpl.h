#ifndef CARDREPOSITORYDBIMPL_H
#define CARDREPOSITORYDBIMPL_H
#include "repository/cardrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"


class CardRepositoryDBImpl : public CardRepository
{
public:
    CardEntity getById(long) override;
    std::vector<CardEntity> getAll() override;
    void setById(long, CardEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    CardEntity getByCardId(long long cardId);
    std::vector<CardEntity> getCardsDependantOnThisByReserve(long id);
    std::vector<CardEntity> getCardsDependantOnThisByOverflow(long id);
    static CardRepository* getInstance();
protected:
    CardRepositoryDBImpl();
    ~CardRepositoryDBImpl(){} // destructor for _rep is called from global window destructor
private:
    static CardRepository* _rep;
    DBManager* _db_manager;
};

#endif // CARDREPOSITORYDBIMPL_H
