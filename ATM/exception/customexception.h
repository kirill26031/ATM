#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H


class CustomException
{
public:
    CustomException(const std::string&);
    ~CustomException(){}
    std::string _message;
};

#endif // CUSTOMEXCEPTION_H
