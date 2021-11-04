#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H
#include "customexception.h"

class NotFoundException : public CustomException
{
public:
    NotFoundException(const std::string&);
    ~NotFoundException(){}


};

#endif // NOTFOUNDEXCEPTION_H
