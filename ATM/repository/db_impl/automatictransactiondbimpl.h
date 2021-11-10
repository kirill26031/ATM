#ifndef AUTOMATICTRANSACTIONDBIMPL_H
#define AUTOMATICTRANSACTIONDBIMPL_H
#include "repository/automatictransactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"
#include "repository/vector_impl/automatictransactionrepositoryvectorimpl.h"


class AutomaticTransactionRepositoryDBImpl : public AutomaticTransactionRepository
{
public:
    AutomaticTransactionEntity getById(long) override;
    std::vector<AutomaticTransactionEntity> getAll() override;
    void setById(long, const AutomaticTransactionEntity&) override;
    void deleteById(long) override;
    void clearAll() override {};
    bool existsById(long) override;
    static AutomaticTransactionRepository* getInstance();
    ~AutomaticTransactionRepositoryDBImpl(){} // destructor for _rep is called from global window destructor

protected:
    AutomaticTransactionRepositoryDBImpl();
private:
    void fillCache(const std::vector<AutomaticTransactionEntity>& vector);

    static AutomaticTransactionRepository* _rep;
    AutomaticTransactionRepository* _cache;
    bool _cache_modified;
    DBManager* _db_manager;
};
#endif // AUTOMATICTRANSACTIONDBIMPL_H
