#ifndef USERREPOSITORYDBIMPL_H
#define USERREPOSITORYDBIMPL_H
#include "repository/userrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"


class UserRepositoryDBImpl : public UserRepository
{
public:
    UserEntity getById(long) override;
    std::vector<UserEntity> getAll() override;
    void setById(long, UserEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    static UserRepository* getInstance();
protected:
    UserRepositoryDBImpl();
    ~UserRepositoryDBImpl(){} // destructor for _rep is called from global window destructor
private:
    static UserRepository* _rep;
    DBManager* _db_manager;
};

#endif // USERREPOSITORYDBIMPL_H
