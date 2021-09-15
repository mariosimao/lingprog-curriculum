#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "StudentCliController.h"
#include "../../Application/PlanSemester.h"
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

void StudentCliController::planSemester(vector<string> arguments)
{
    if (arguments.size() < 2) {
        throw "Missing arguments";
    }

    string studentId = arguments[0];
    string name      = arguments[1];
    string startDate = arguments[2];
    string endDate   = arguments[3];

    boost::gregorian::date start(boost::gregorian::from_simple_string(startDate));
    boost::gregorian::date end(boost::gregorian::from_simple_string(endDate));

    PlanSemester handler(this->_studentRepository);

    cout << "Before execute" << "\n";

    string id = handler.execute(studentId, name, start, end);

    cout << "Semester successfully planned" << "\n" << "\n";
    cout << "Id:\t\t" << id << "\n";
    cout << "Name:\t\t" << name << "\n";
    cout << "Start:\t\t" << startDate << "\n";
    cout << "End:\t\t" << endDate << "\n";

    return;
}
