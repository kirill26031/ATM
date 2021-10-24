#ifndef VECTOR
#define VECTOR
#include <vector>
#endif



#ifndef REPOSITORY_H
#define REPOSITORY_H

template <typename T>
class Repository
{
public:
    Repository() {}
    ~Repository() {}


    virtual const std::vector<T>& getAll(){
        return _entities;
    }

    virtual const T& getById(long) = 0;
    virtual void setById(long, T&) = 0;
    virtual void deleteById(long) = 0;

protected:
    std::vector<T> _entities;
};

#endif // REPOSITORY_H
