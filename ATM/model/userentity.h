#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef USERENTITY_H
#define USERENTITY_H

#include "entity.h"


class UserEntity : public Entity
{
public:
    UserEntity(long id, const std::string& name);
    ~UserEntity();
    const std::string& name();
    std::string _name;
private:
    UserEntity(const UserEntity&) = delete;
    void operator=(const UserEntity&) = delete;
};

#endif // USERENTITY_H
