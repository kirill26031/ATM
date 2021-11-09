#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

template <typename T>
class Repository
{
public:
    virtual std::vector<T> getAll() = 0;
    virtual T getById(long) = 0;
    virtual void setById(long, const T&) = 0;
    virtual void deleteById(long) = 0;
    virtual void clearAll() = 0;
    virtual bool existsById(long) = 0;
    virtual ~Repository() {}

protected:
    Repository() {}
};

#endif // REPOSITORY_H
