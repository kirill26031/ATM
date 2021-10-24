#ifndef CUSTOM_EXCEPTION
#define CUSTOM_EXCEPTION
#include "customexception.h"
#endif

#ifndef INCORRECTCARDAUTHINFOEXCEPTION_H
#define INCORRECTCARDAUTHINFOEXCEPTION_H

class IncorrectCardAuthInfoException : public CustomException
{
public:
    IncorrectCardAuthInfoException(const std::string&);
    ~IncorrectCardAuthInfoException(){}
};

#endif // INCORRECTCARDAUTHINFOEXCEPTION_H
