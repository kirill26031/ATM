#ifndef TRANSACTIONREPOSITORYDBIMPL_H
#define TRANSACTIONREPOSITORYDBIMPL_H
#include "repository/transactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"
#include "repository/vector_impl/transactionrepositoryvectorimpl.h"

class TransactionRepositoryDBImpl : public TransactionRepository
{
public:
    TransactionEntity getById(long) override;
    std::vector<TransactionEntity> getAll() override;
    void setById(long, const TransactionEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    static TransactionRepository* getInstance();
protected:
    TransactionRepositoryDBImpl();
    ~TransactionRepositoryDBImpl(){} // destructor for _rep is called from global window destructor
private:
    void fillCache(const std::vector<TransactionEntity>& vector);

    static TransactionRepository* _rep;
    TransactionRepository* _cache;
    bool _cache_modified;
    DBManager* _db_manager;
};;

#endif // TRANSACTIONREPOSITORYDBIMPL_H
