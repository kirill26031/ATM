#ifndef CUSTOM_EXCEPTION
#define CUSTOM_EXCEPTION
#include "customexception.h"
#endif

#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H


class NotFoundException : public CustomException
{
public:
    NotFoundException(const std::string&);
    ~NotFoundException(){}
};

#endif // NOTFOUNDEXCEPTION_H
