#include <string>
#include <set>

#include "SubjectHttpController.h"
#include "../../Application/RegisterSubject.h"

using namespace web::json;

SubjectHttpController::SubjectHttpController(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

http_response SubjectHttpController::registerSubject(http_request& request)
{
    value body = request.extract_json().get();
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

    value responseBody = value::object();
    responseBody["id"] = value::string(id);

    http_response response(status_codes::Created);
    response.set_body(responseBody);

    return response;
}