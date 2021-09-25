#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "StudentCliController.h"
#include "../../Application/PlanSemester.h"
#include "../../Application/PlanSubjectAttempt.h"
#include "../../Application/RegisterStudent.h"

using namespace std;

StudentCliController::StudentCliController(
    IStudentRepository& studentRepository,
    ISubjectRepository& subjectRepository
): _studentRepository(studentRepository), _subjectRepository(subjectRepository)
{}

void StudentCliController::registerStudent(vector<string> arguments)
{
    if (arguments.size() < 1) {
        throw "Missing arguments";
    }

    string studentId = arguments[0];

    RegisterStudent handler(this->_studentRepository);
    string id = handler.execute(studentId);

    cout << "Student successfully registered" << "\n" << "\n";

    return;
}

void StudentCliController::planSemester(vector<string> arguments)
{
    if (arguments.size() < 3) {
        throw "Missing arguments";
    }

    string studentId = arguments[0];
    string startDate = arguments[1];
    string endDate   = arguments[2];

    boost::gregorian::date start(boost::gregorian::from_simple_string(startDate));
    boost::gregorian::date end(boost::gregorian::from_simple_string(endDate));

    PlanSemester handler(this->_studentRepository);

    handler.execute(studentId, start, end);

    cout << "Semester successfully planned.\n";

    return;
}

void StudentCliController::planSubjectAttempt(vector<string> arguments)
{
    if (arguments.size() < 3) {
        throw "Missing arguments";
    }

    string studentId = arguments[0];
    string semesterId = arguments[1];
    string subjectId = arguments[2];

    PlanSubjectAttempt handler(this->_studentRepository);

    string id = handler.execute(studentId, semesterId, subjectId);

    cout << "Subject successfully planned.\n";

    return;
}
