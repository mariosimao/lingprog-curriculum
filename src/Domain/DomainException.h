#ifndef DOMAIN_EXCEPTION_H
#define DOMAIN_EXCEPTION_H
#include <exception>
#include <string>

using namespace std;

class DomainException: public exception
{
    public:
        string message;
        DomainException(string message);
        const char* what();
};
#endif
