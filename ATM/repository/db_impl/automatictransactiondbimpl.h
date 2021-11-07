#ifndef AUTOMATICTRANSACTIONDBIMPL_H
#define AUTOMATICTRANSACTIONDBIMPL_H
#include "repository/automatictransactionrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"


class AutomaticTransactionDBImpl
{
    class AutomaticTransactionRepositoryDBImpl : public AutomaticTransactionRepository
    {
    public:
        AutomaticTransactionEntity getById(long) override;
        std::vector<AutomaticTransactionEntity> getAll() override;
        void setById(long, AutomaticTransactionEntity&) override;
        void deleteById(long) override;
        bool existsById(long) override;
        static AutomaticTransactionRepository* getInstance();
    protected:
        AutomaticTransactionRepositoryDBImpl();
        ~AutomaticTransactionRepositoryDBImpl(){} // destructor for _rep is called from global window destructor
    private:
        static AutomaticTransactionRepository* _rep;
        DBManager* _db_manager;
    };
};

#endif // AUTOMATICTRANSACTIONDBIMPL_H
