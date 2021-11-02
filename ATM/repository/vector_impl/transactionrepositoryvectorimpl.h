#ifndef TRANSACTIONREPOSITORYVECTORIMPL_H
#define TRANSACTIONREPOSITORYVECTORIMPL_H

#include "repository/transactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>

class TransactionRepositoryVectorImpl : public TransactionRepository
{
public:
    const TransactionEntity& getById(long) override;
    const std::vector<TransactionEntity>& getAll() override;
    void setById(long, TransactionEntity&) override;
    void deleteById(long) override;
    static TransactionRepository* getInstance();
protected:
    TransactionRepositoryVectorImpl();
    ~TransactionRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor
private:
    std::vector<TransactionEntity> _entities;
    static TransactionRepository* _rep;
};

#endif // TRANSACTIONREPOSITORYVECTORIMPL_H