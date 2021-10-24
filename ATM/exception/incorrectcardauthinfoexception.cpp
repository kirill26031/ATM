#include "incorrectcardauthinfoexception.h"

IncorrectCardAuthInfoException::IncorrectCardAuthInfoException(const std::string& message) :
    CustomException(message)
{

}
