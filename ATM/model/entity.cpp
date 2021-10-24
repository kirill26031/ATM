#include "entity.h"

Entity::Entity(long id) : _id(id)
{

}

Entity& Entity::operator=(const Entity& other)
{
    _id = other._id;
    return *this;
}
