#ifndef TRANSACTIONREPOSITORYDBIMPL_H
#define TRANSACTIONREPOSITORYDBIMPL_H
#include "repository/transactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"

class TransactionRepositoryDBImpl : public TransactionRepository
{
public:
    TransactionEntity getById(long) override;
    std::vector<TransactionEntity> getAll() override;
    void setById(long, TransactionEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    static TransactionRepository* getInstance();
protected:
    TransactionRepositoryDBImpl();
    ~TransactionRepositoryDBImpl(){} // destructor for _rep is called from global window destructor
private:
    static TransactionRepository* _rep;
    DBManager* _db_manager;
};;

#endif // TRANSACTIONREPOSITORYDBIMPL_H
