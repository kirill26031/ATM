#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    Entity(long id);
    ~Entity(){}
    Entity& operator=(const Entity& other);
    Entity(const Entity& other);

    const long& id() const {return _id;}
protected:
    long _id;
};

#endif // ENTITY_H
