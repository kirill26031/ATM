//#ifndef STRING
//#define STRING
#include <string>
//#endif

#ifndef USERENTITY_H
#define USERENTITY_H

#include "entity.h"


class UserEntity : public Entity
{
public:
    UserEntity(long id, const std::string& name);
    ~UserEntity();
    const std::string& name() const {return _name;}
private:
    std::string _name;

};

#endif // USERENTITY_H
