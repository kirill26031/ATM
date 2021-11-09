#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <model/userentity.h>
#include "repository.h"
#include    <exception/notfoundexception.h>

class UserRepository : public Repository<UserEntity>
{
public:
    virtual ~UserRepository() {}
protected:
    UserRepository() : Repository<UserEntity>() {}
};

#endif // USERREPOSITORY_H
