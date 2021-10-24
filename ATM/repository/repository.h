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
    ~Repository()
    {

    }
    virtual const T& getById(long) = 0;
    virtual const std::vector<T>& getAll() = 0;
    virtual void setById(long, T&) = 0;
    virtual void deleteById(long) = 0;


};

#endif // REPOSITORY_H
