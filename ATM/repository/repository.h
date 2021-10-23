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
    virtual ~Repository() = 0;
//    Repository* getInstance();
    virtual const T& getById(long);
    virtual const std::vector<T>& getAll();
    virtual void setById(long, T&);
    virtual void deleteById(long);


};

#endif // REPOSITORY_H
