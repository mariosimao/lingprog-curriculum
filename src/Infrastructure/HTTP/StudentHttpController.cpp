#include <boost/date_time/gregorian/gregorian.hpp>
#include "StudentHttpController.h"
#include "../../Application/EditStudentSemester.h"
#include "../../Application/ListStudentSemesters.h"
#include "../../Application/PlanSemester.h"
#include "../../Application/PlanSubjectAttempt.h"
#include "../../Application/RegisterStudent.h"
#include "../../Application/RemoveStudentSemester.h"
#include "../Persistence/SqlStudentRepository.h"
#include "../Persistence/SqlSubjectRepository.h"

using namespace std;

StudentHttpController::StudentHttpController(
    IStudentRepository& studentRepository,
    ISubjectRepository& subjectRepository
): _studentRepository(studentRepository), _subjectRepository(subjectRepository)
{}

void StudentHttpController::registerStudent(http::http_request& request)
{
    web::json::value body = request.extract_json().get();
    string id = body["id"].as_string();

    RegisterStudent handler(this->_studentRepository);
    handler.execute(id);

    request.reply(http::status_codes::Created);
    return;
}

void StudentHttpController::listSemesters(http::http_request& request, string studentId)
{
    ListStudentSemesters handler(this->_studentRepository);
    vector<StudentSemesterView> semesters = handler.execute(studentId);

    web::json::value response = web::json::value::object();
    response["semesters"] = web::json::value::array();

    int i = 0;
    for (auto semester: semesters) {
        web::json::value semesterJson = web::json::value::object();
        semesterJson["id"] = web::json::value::string(semester.id);
        semesterJson["name"] = web::json::value::string(semester.name);
        semesterJson["startDate"] = web::json::value::string(semester.startDate);
        semesterJson["endDate"] = web::json::value::string(semester.endDate);

        response["semesters"][i] = semesterJson;
        i++;
    }

    request.reply(http::status_codes::OK, response);
    return;
}

void StudentHttpController::planSemester(http::http_request& request, string studentId)
{
    web::json::value body = request.extract_json().get();

    string startDate = body["startDate"].as_string();
    string endDate = body["endDate"].as_string();

    boost::gregorian::date start(boost::gregorian::from_simple_string(startDate));
    boost::gregorian::date end(boost::gregorian::from_simple_string(endDate));

    PlanSemester handler(this->_studentRepository);
    string semesterId = handler.execute(studentId, start, end);

    web::json::value response = web::json::value::object();
    response["id"] = web::json::value::string(semesterId);

    request.reply(http::status_codes::Created, response);
    return;
}

void StudentHttpController::editSemester(
    http::http_request& request,
    string studentId,
    string semesterId
) {
    web::json::value body = request.extract_json().get();

    string name = body["name"].as_string();
    string startDate = body["startDate"].as_string();
    string endDate = body["endDate"].as_string();

    boost::gregorian::date start(boost::gregorian::from_simple_string(startDate));
    boost::gregorian::date end(boost::gregorian::from_simple_string(endDate));

    EditStudentSemester handler(this->_studentRepository);
    handler.execute(
        studentId,
        semesterId,
        name,
        start,
        end
    );

    request.reply(http::status_codes::NoContent);
    return;
}

void StudentHttpController::removeSemester(
    http::http_request& request,
    string studentId,
    string semesterId
) {
    RemoveStudentSemester handler(this->_studentRepository);
    handler.execute(studentId, semesterId);

    request.reply(http::status_codes::NoContent);
    return;
}

void StudentHttpController::planSubjectAttempt(
    http::http_request& request,
    string studentId,
    string semesterId
) {
    web::json::value body = request.extract_json().get();

    string subjectId = body["subjectId"].as_string();

    PlanSubjectAttempt handler(this->_studentRepository);
    string attemptId = handler.execute(
        studentId,
        semesterId,
        subjectId
    );

    web::json::value response = web::json::value::object();
    response["id"] = web::json::value::string(attemptId);

    request.reply(http::status_codes::Created, response);
    return;
}
