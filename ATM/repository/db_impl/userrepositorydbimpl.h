#ifndef USERREPOSITORYDBIMPL_H
#define USERREPOSITORYDBIMPL_H
#include "repository/userrepository.h"
#include "exception/notfoundexception.h"
#include <string>
#include "dbmanager.h"
#include "repository/vector_impl/userrepositoryvectorimpl.h"


class UserRepositoryDBImpl : public UserRepository
{
public:
    UserEntity getById(long) override;
    std::vector<UserEntity> getAll() override;
    void setById(long, const UserEntity&) override;
    void deleteById(long) override;
    void clearAll() override {};

    bool existsById(long) override;
    static UserRepository* getInstance();
protected:
    UserRepositoryDBImpl();
    ~UserRepositoryDBImpl(){} // destructor for _rep is called from global window destructor
private:
    void fillCache(const std::vector<UserEntity>& vector);

    static UserRepository* _rep;
    UserRepository* _cache;
    bool _cache_modified;
    DBManager* _db_manager;
};

#endif // USERREPOSITORYDBIMPL_H
