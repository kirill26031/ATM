#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    Entity(long id);
    ~Entity(){}
    const long& id(){return _id;}

    long _id;
};

#endif // ENTITY_H
