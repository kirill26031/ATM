#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include "customexception.h"

class SQLException : public CustomException
{
public:
    SQLException(std::string message) :
        CustomException(std::string("SQLException: ").append(message)) {}
    ~SQLException(){}
};

#endif // SQLEXCEPTION_H
