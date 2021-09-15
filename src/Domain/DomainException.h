#ifndef DOMAIN_EXCEPTION_H
#define DOMAIN_EXCEPTION_H
#include <exception>
#include <string>

using namespace std;

class DomainException
{
    public:
        string _message;
        DomainException(string message);
        string what();
};
#endif
