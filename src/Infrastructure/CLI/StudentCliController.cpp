#include <iostream>
#include "StudentCliController.h"
#include "../../Application/RegisterStudent.h"
#include "../../Domain/IStudentRepository.h"

using namespace std;

StudentCliController::StudentCliController(IStudentRepository* studentRepository)
{
    this->_studentRepository = studentRepository;
}

void StudentCliController::registerStudent(vector<string> arguments)
{
    if (arguments.size() < 2) {
        throw "Missing arguments";
    }

    string name = arguments[0];
    string curriculumId = arguments[1];

    RegisterStudent handler(this->_studentRepository);
    string id = handler.execute(name, curriculumId);

    cout << "Student successfully registered" << "\n" << "\n";
    cout << "Id:\t\t" << id << "\n";
    cout << "Name:\t\t" << name << "\n";

    return;
}

    return;
}
