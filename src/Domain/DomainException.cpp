#include "DomainException.h"

DomainException::DomainException(string message)
{
    this->_message = message;
}

string DomainException::what()
{
    return this->_message;
}
