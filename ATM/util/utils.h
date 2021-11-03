#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>

long generateId()
{
    return rand();
}

long long generateCardId()
{
    long long res = 0;
    for(size_t i=0; i<16; ++i)
    {
        res = res*10+(rand()%10);
    }
    return res;
}

int generatePin()
{
    int res = 0;
    for(size_t i=0; i<4; ++i)
    {
        res = res*10+(rand()%10);
    }
    return res;
}

#endif // UTILS_H
