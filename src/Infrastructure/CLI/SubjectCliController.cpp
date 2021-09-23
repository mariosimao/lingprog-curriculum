#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "SubjectCliController.h"
#include "../../Application/AddPrerequisiteHandler.h"
#include "../../Application/RegisterSubject.h"
#include "../../Domain/ISubjectRepository.h"

using namespace std;

SubjectCliController::SubjectCliController(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

void SubjectCliController::registerSubject(vector<string> arguments)
{
    if (arguments.size() < 3) {
        throw "Missing arguments";
    }

    string code = arguments[0];
    string name = arguments[1];
    int credits = stoi(arguments[2]);
    set<string> prerequisites;
    set<string> corequisites;

    RegisterSubject handler(this->_subjectRepository);
    string id = handler.execute(code, name, credits, prerequisites, corequisites);

    cout << "Subject successfully registered" << "\n" << "\n";
    cout << "Id:\t\t" << id << "\n";
    cout << "Name:\t\t" << name << "\n";
    cout << "Code:\t\t" << code << "\n";
    cout << "Credits:\t" << credits << "\n";

    return;
}

void SubjectCliController::addPrerequisite(vector<string> arguments)
{
    if (arguments.size() < 2) {
        throw "Missing arguments";
    }

    string subjectId = arguments[0];
    string prerequisiteId = arguments[1];

    AddPrerequisiteHandler handler(this->_subjectRepository);
    handler.execute(subjectId, prerequisiteId);

    cout << "Prerequisite successfully added." << "\n" << "\n";

    return;
}
