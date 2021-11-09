#include "utils.h"

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

long long readCardNumber(std::string s)
{
    int n = 16;
    if(s.length() != n) return -1;
    long long res = 0;
    for(int i=0 ; i<n; ++i)
    {
        res = res*10+(s.at(i)-'0');
    }
    return res;
}

long readPin(std::string s)
{
    int n = 4;
    if(s.length() != n) return -1;
    long res = 0;
    for(int i=0 ; i<n; ++i)
    {
        res = res*10+(s.at(i)-'0');
    }
    return res;
}

std::string printCardNumber(long long card_number)
{
    int n = 16;
    std::string res("0123012301230123");
    for(int i=0; i<n; ++i)
    {
        res.at(n-1-i) = (card_number%10 + '0');
        card_number /= 10;
    }
    return res;
}

std::string printPin(long pin)
{
    int n = 4;
    std::string res("0123");
    for(int i=0; i<n; ++i)
    {
        res.at(n-1-i) = (pin%10 + '0');
        pin /= 10;
    }
    return res;
}
