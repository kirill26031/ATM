#ifndef CIRCULARDEPENDANCYEXCEPTION_H
#define CIRCULARDEPENDANCYEXCEPTION_H

#include "customexception.h"

class CircularDependancyException : public CustomException
{
public:
    CircularDependancyException(std::string message) :
        CustomException(std::string("CircularDependencyException: ").append(message)) {}
    ~CircularDependancyException(){}
};

#endif // CIRCULARDEPENDANCYEXCEPTION_H
