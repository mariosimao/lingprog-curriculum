#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "SubjectCliController.h"
#include "../../Application/RegisterSubjectHandler.h"
#include "../../Domain/ISubjectRepository.h"

using namespace std;

SubjectCliController::SubjectCliController(ISubjectRepository* subjectRepository)
{
    this->_subjectRepository = subjectRepository;
}

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

    RegisterSubjectHandler handler(this->_subjectRepository);
    string id = handler.execute(code, name, credits, prerequisites, corequisites);

    cout << "Subject successfully registered" << endl << endl;
    cout << "Id:\t\t" << id << endl;
    cout << "Name:\t\t" << name << endl;
    cout << "Code:\t\t" << code << endl;
    cout << "Credits:\t" << credits << endl;

    return;
}
