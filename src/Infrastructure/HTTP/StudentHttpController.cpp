#include "StudentHttpController.h"
#include "../../Application/RegisterStudent.h"
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
