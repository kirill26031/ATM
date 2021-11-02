#ifndef AUTOMATICTRANSACTIONREPOSITORYVECTORIMPL_H
#define AUTOMATICTRANSACTIONREPOSITORYVECTORIMPL_H

#include "repository/automatictransactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>

class AutomaticTransactionRepositoryVectorImpl : public AutomaticTransactionRepository
{
public:
    const AutomaticTransactionEntity& getById(long) override;
    const std::vector<AutomaticTransactionEntity>& getAll() override;
    void setById(long, AutomaticTransactionEntity&) override;
    void deleteById(long) override;
    static AutomaticTransactionRepository* getInstance();
protected:
    AutomaticTransactionRepositoryVectorImpl();
    ~AutomaticTransactionRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor
private:
    std::vector<AutomaticTransactionEntity> _entities;
    static AutomaticTransactionRepository* _rep;
};

#endif // AUTOMATICTRANSACTIONREPOSITORYVECTORIMPL_H
