#include <string>
#include <set>
#include "Subject.h"

Subject::Subject(
    const string code,
    const string name,
    const int credits,
    const set<string> prerequisites,
    const set<string> corequisites
) {
    this->_code = code;
    this->_name = name;
    this->_credits = credits;
    this->_prerequisites = prerequisites;
    this->_corequisites = corequisites;
}

void Subject::addPrerequisite(const string prerequisite)
{
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
