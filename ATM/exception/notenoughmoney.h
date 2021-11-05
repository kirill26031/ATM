#ifndef NOTENOUGHMONEY_H
#define NOTENOUGHMONEY_H

#include "customexception.h"
#include <string>

class NotEnoughMoney : public CustomException
{
public:
    NotEnoughMoney(std::string message) : CustomException(std::string("NotEnoughMoney: ").append(message)) {}
    ~NotEnoughMoney(){}
};

#endif // NOTENOUGHMONEY_H
