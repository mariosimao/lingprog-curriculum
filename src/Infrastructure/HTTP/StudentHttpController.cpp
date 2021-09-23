#include <boost/date_time/gregorian/gregorian.hpp>
#include "StudentHttpController.h"
#include "../../Application/RegisterStudent.h"
#include "../../Application/PlanSemester.h"
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
