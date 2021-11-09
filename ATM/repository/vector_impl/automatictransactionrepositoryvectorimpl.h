#ifndef AUTOMATICTRANSACTIONREPOSITORYVECTORIMPL_H
#define AUTOMATICTRANSACTIONREPOSITORYVECTORIMPL_H

#include "repository/automatictransactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>

class AutomaticTransactionRepositoryVectorImpl : public AutomaticTransactionRepository
{
public:
    AutomaticTransactionEntity getById(long) override;
    std::vector<AutomaticTransactionEntity> getAll() override;
    void setById(long, const AutomaticTransactionEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    void clearAll() override;
    static AutomaticTransactionRepository* getInstance();
    ~AutomaticTransactionRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor

protected:
    AutomaticTransactionRepositoryVectorImpl();
private:
    std::vector<AutomaticTransactionEntity> _entities;
    static AutomaticTransactionRepository* _rep;
};

#endif // AUTOMATICTRANSACTIONREPOSITORYVECTORIMPL_H
