#include <string>
#include <set>

#include "SubjectHttpController.h"
#include "../../Application/RegisterSubject.h"

using namespace std;

SubjectHttpController::SubjectHttpController(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

void SubjectHttpController::registerSubject(http::http_request& request)
{
    web::json::value body = request.extract_json().get();
    string code = body["code"].as_string();
    string name = body["name"].as_string();
    float credits = body["credits"].as_integer();

    set<string> prerequisites;
    for (auto prerequisite: body["prerequisites"].as_array()) {
        prerequisites.insert(prerequisite.as_string());
    }

    set<string> corequisites;
    for (auto corequisite: body["corequisites"].as_array()) {
        corequisites.insert(corequisite.as_string());
    }

    RegisterSubject handler(this->_subjectRepository);
    string id = handler.execute(code, name, credits, prerequisites, corequisites);

    web::json::value response = web::json::value::object();
    response["id"] = web::json::value::string(id);

    request.reply(http::status_codes::Created, response);
    return;
}