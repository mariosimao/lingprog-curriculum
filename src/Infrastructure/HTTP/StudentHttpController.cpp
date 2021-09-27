#include <boost/date_time/gregorian/gregorian.hpp>
#include "StudentHttpController.h"
#include "../../Application/EditStudentSemester.h"
#include "../../Application/EditSubjectAttempt.h"
#include "../../Application/ListStudentSemesters.h"
#include "../../Application/ListSubjectAttemptsBySemester.h"
#include "../../Application/PlanSemester.h"
#include "../../Application/PlanSubjectAttempt.h"
#include "../../Application/RegisterStudent.h"
#include "../../Application/RemoveStudentSemester.h"
#include "../../Application/RemoveSubjectAttempt.h"
#include "../Persistence/SqlStudentRepository.h"
#include "../Persistence/SqlSubjectRepository.h"

using namespace web::json;

StudentHttpController::StudentHttpController(
    IStudentRepository& studentRepository,
    ISubjectRepository& subjectRepository
): _studentRepository(studentRepository), _subjectRepository(subjectRepository)
{}

http_response StudentHttpController::registerStudent(http_request& request)
{
    value body = request.extract_json().get();
    string id = body["id"].as_string();

    RegisterStudent handler(this->_studentRepository);
    handler.execute(id);

    return http_response(status_codes::Created);
}

http_response StudentHttpController::listSemesters(http_request& request, string studentId)
{
    ListStudentSemesters handler(this->_studentRepository);
    vector<StudentSemesterView> semesters = handler.execute(studentId);

    value responseBody = value::object();
    responseBody["semesters"] = value::array();

    int i = 0;
    for (auto semester: semesters) {
        value semesterJson = value::object();
        semesterJson["id"] = value::string(semester.id);
        semesterJson["name"] = value::string(semester.name);
        semesterJson["startDate"] = value::string(semester.startDate);
        semesterJson["endDate"] = value::string(semester.endDate);

        responseBody["semesters"][i] = semesterJson;
        i++;
    }

    http_response response(status_codes::OK);
    response.set_body(responseBody);

    return response;
}

http_response StudentHttpController::planSemester(http_request& request, string studentId)
{
    value body = request.extract_json().get();

    string startDate = body["startDate"].as_string();
    string endDate = body["endDate"].as_string();

    boost::gregorian::date start(boost::gregorian::from_simple_string(startDate));
    boost::gregorian::date end(boost::gregorian::from_simple_string(endDate));

    PlanSemester handler(this->_studentRepository);
    StudentSemesterView semester = handler.execute(studentId, start, end);

    value responseBody = value::object();
    responseBody["id"] = value::string(semester.id);
    responseBody["name"] = value::string(semester.name);
    responseBody["startDate"] = value::string(semester.startDate);
    responseBody["endDate"] = value::string(semester.endDate);

    http_response response(status_codes::Created);
    response.set_body(responseBody);

    return response;
}

http_response StudentHttpController::editSemester(
    http_request& request,
    string studentId,
    string semesterId
) {
    value body = request.extract_json().get();

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

    return http_response(status_codes::NoContent);
}

http_response StudentHttpController::removeSemester(
    http_request& request,
    string studentId,
    string semesterId
) {
    RemoveStudentSemester handler(this->_studentRepository);
    handler.execute(studentId, semesterId);

    return http_response(status_codes::NoContent);
}

http_response StudentHttpController::listSubjectAttemptsBySemester(
    http_request& request,
    string studentId,
    string semesterId
) {
    ListSubjectAttemptsBySemester handler(this->_studentRepository);
    vector<SubjectAttemptView> attempts = handler.execute(studentId, semesterId);

    value responseBody = value::object();
    value attemptsArray = value::array();
    int i = 0;
    for (auto attempt: attempts) {
        value attemptJson = value::object();
        attemptJson["id"] = value::string(attempt.id);
        attemptJson["subjectId"] = value::string(attempt.subjectId);
        attemptJson["professor"] = attempt.professor.empty() ?
            value::null() : value::string(attempt.professor);
        attemptJson["grade"] = (attempt.grade == -1) ?
            value::null() : value::number(attempt.grade);

        attemptsArray[i] = attemptJson;
        i++;
    }

    responseBody["subjectAttempts"] = attemptsArray;

    http_response response(status_codes::OK);
    response.set_body(responseBody);

    return response;
}

http_response StudentHttpController::planSubjectAttempt(
    http_request& request,
    string studentId,
    string semesterId
) {
    value body = request.extract_json().get();

    string subjectId = body["subjectId"].as_string();

    PlanSubjectAttempt handler(this->_studentRepository);
    string attemptId = handler.execute(
        studentId,
        semesterId,
        subjectId
    );

    value responseBody = value::object();
    responseBody["id"] = value::string(attemptId);

    http_response response(status_codes::OK);
    response.set_body(responseBody);

    return response;
}

http_response StudentHttpController::editSubjectAttempt(
    http_request& request,
    string studentId,
    string semesterId,
    string attemptId
) {
    value body = request.extract_json().get();

    string newProfessor = body["professor"].is_null() ? "" : body["professor"].as_string();
    float newGrade = body["grade"].is_null() ? -1 : body["grade"].as_double();

    EditSubjectAttempt handler(this->_studentRepository);
    handler.execute(studentId, semesterId, attemptId, newProfessor, newGrade);

    http_response response(status_codes::NoContent);
    return response;
}

http_response StudentHttpController::removeSubjectAttempt(
    http_request& request,
    string studentId,
    string semesterId,
    string attemptId
) {
    RemoveSubjectAttempt handler(this->_studentRepository);
    handler.execute(studentId, semesterId, attemptId);

    http_response response(status_codes::NoContent);
    return response;
}
