#include "userentity.h"

UserEntity::UserEntity(long id, const std::string& name) : Entity(id), _name(name)
{
}

UserEntity::~UserEntity(){}

//const std::string& UserEntity::name()
//{
//    return _name;
//}
