#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <string>

long generateId();

long long generateCardId();

int generatePin();

long long readCardNumber(std::string s);

long readPin(std::string s);

std::string printCardNumber(long long card_number);

std::string printPin(long pin);

#endif // UTILS_H
