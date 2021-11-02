#ifndef USERREPOSITORYVECTORIMPL_H
#define USERREPOSITORYVECTORIMPL_H

#include "repository/userrepository.h"
#include "exception/notfoundexception.h"
#include <string>

class UserRepositoryVectorImpl : public UserRepository
{
public:
    const UserEntity& getById(long) override;
    const std::vector<UserEntity>& getAll() override;
    void setById(long, UserEntity&) override;
    void deleteById(long) override;
    static UserRepository* getInstance();
protected:
    UserRepositoryVectorImpl();
    ~UserRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor
private:
    std::vector<UserEntity> _entities;
    static UserRepository* _rep;
};

#endif // USERREPOSITORYVECTORIMPL_H