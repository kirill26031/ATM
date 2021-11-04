#ifndef LOGICCONFLICTEXCEPTION_H
#define LOGICCONFLICTEXCEPTION_H
#include <string>
#include "customexception.h"

class LogicConflictException : public CustomException
{
public:
    LogicConflictException(std::string message) :
        CustomException(std::string("LogicConflictException: ").append(message)) {}
    ~LogicConflictException(){}
};

#endif // LOGICCONFLICTEXCEPTION_H
