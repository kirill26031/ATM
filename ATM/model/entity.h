#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    Entity(long id);
    ~Entity(){}
    Entity& operator=(const Entity& other);
    Entity(const Entity& other);

    long _id;
};

#endif // ENTITY_H
