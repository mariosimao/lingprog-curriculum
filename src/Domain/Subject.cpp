#include <string>
#include <set>
#include "Subject.h"
#include "DomainException.h"

Subject::Subject(
    const string id,
    const string code,
    const string name,
    const int credits,
    const set<string> prerequisites,
    const set<string> corequisites
) {
    this->_id = id;
    this->_code = code;
    this->_name = name;
    this->_credits = credits;
    this->_prerequisites = prerequisites;
    this->_corequisites = corequisites;
}

string Subject::getId()
{
    return this->_id;
}

string Subject::getCode()
{
    return this->_code;
}

string Subject::getName()
{
    return this->_name;
}

int Subject::getCredits()
{
    return this->_credits;
}

set<string> Subject::getPrerequisites()
{
    return this->_prerequisites;
}

set<string> Subject::getCorequisites()
{
    return this->_corequisites;
}

void Subject::addPrerequisite(const string prerequisite)
{
    if (prerequisite == this->_id) {
        throw DomainException(string("Cannot add same subject as prerequisite."));
    }

    this->_prerequisites.insert(prerequisite);
}

void Subject::removePrequisite(const string prerequisite)
{
    this->_prerequisites.erase(prerequisite);
}

void Subject::addCorequisite(const string corequisite)
{
    this->_corequisites.insert(corequisite);
}

void Subject::removeCorequisite(const string corequisite)
{
    this->_corequisites.erase(corequisite);
}
