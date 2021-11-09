#ifndef USERREPOSITORYVECTORIMPL_H
#define USERREPOSITORYVECTORIMPL_H

#include "repository/userrepository.h"
#include "exception/notfoundexception.h"
#include <string>

class UserRepositoryVectorImpl : public UserRepository
{
public:
    UserEntity getById(long) override;
    std::vector<UserEntity> getAll() override;
    void setById(long, const UserEntity&) override;
    void deleteById(long) override;
    bool existsById(long) override;
    void clearAll() override;
    static UserRepository* getInstance();
    ~UserRepositoryVectorImpl(){} // destructor for _rep is called from global window destructor

protected:
    UserRepositoryVectorImpl();
private:
    std::vector<UserEntity> _entities;
    static UserRepository* _rep;
};

#endif // USERREPOSITORYVECTORIMPL_H
