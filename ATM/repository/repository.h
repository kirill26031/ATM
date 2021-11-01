#include <vector>


#ifndef REPOSITORY_H
#define REPOSITORY_H

template <typename T>
class Repository
{
public:
    virtual const std::vector<T>& getAll() = 0;
    virtual const T& getById(long) = 0;
    virtual void setById(long, T&) = 0;
    virtual void deleteById(long) = 0;
protected:
    Repository() {}
    virtual ~Repository() {}
};

#endif // REPOSITORY_H
