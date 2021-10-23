#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H


class NotFoundException
{
public:
    NotFoundException(const std::string&);
    ~NotFoundException(){}

    std::string _message;


};

#endif // NOTFOUNDEXCEPTION_H
