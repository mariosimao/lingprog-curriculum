#include "DomainException.h"

DomainException::DomainException(string message)
{
    this->message = message;
}

const char* DomainException::what()
{
    return this->message.c_str();
}
