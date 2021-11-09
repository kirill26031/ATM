#ifndef CARDREPOSITORYDBIMPL_H
#define CARDREPOSITORYDBIMPL_H
#include "repository/cardrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"
#include "repository/vector_impl/cardrepositoryvectorimpl.h"


class CardRepositoryDBImpl : public CardRepository
{
public:
    CardEntity getById(long) override;
    std::vector<CardEntity> getAll() override;
    void setById(long, const CardEntity&) override;
    void deleteById(long) override;
    void clearAll() override {};

    bool existsById(long) override;
    CardEntity getByCardId(long long cardId);
    std::vector<CardEntity> getCardsDependantOnThisByReserve(long id);
    std::vector<CardEntity> getCardsDependantOnThisByOverflow(long id);
    static CardRepository* getInstance();
    ~CardRepositoryDBImpl(){} // destructor for _rep is called from global window destructor

protected:
    CardRepositoryDBImpl();
private:
    void fillCache(const std::vector<CardEntity>& vector);

    int _counter_of_usages_while_cache_is_modified;
    const int cache_limit = 5;
    CardRepository* _cache;
    bool _cache_modified;
    static CardRepository* _rep;
    DBManager* _db_manager;
};

#endif // CARDREPOSITORYDBIMPL_H
