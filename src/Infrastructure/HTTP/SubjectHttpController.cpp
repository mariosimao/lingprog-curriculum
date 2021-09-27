#include <string>
#include <set>

#include "SubjectHttpController.h"
#include "../../Application/RegisterSubject.h"
#include "../../Application/ListSubjects.h"

using namespace web::json;

SubjectHttpController::SubjectHttpController(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

http_response SubjectHttpController::listSubjects(http_request& request)
{
    ListSubjects handler(this->_subjectRepository);
    vector<SubjectView> subjects = handler.execute();

    value responseBody = value::object();
    value subjectsArray = value::array();
    int i = 0;
    for (auto subject: subjects) {
        value subjectJson = value::object();
        subjectJson["id"] = value::string(subject.id);
        subjectJson["code"] = value::string(subject.code);
        subjectJson["name"] = value::string(subject.name);
        subjectJson["credits"] = value::number(subject.credits);

        subjectsArray[i] = subjectJson;
        i++;
    }
    responseBody["subjects"] = subjectsArray;

    http_response response(status_codes::OK);
    response.set_body(responseBody);

    return response;
}

http_response SubjectHttpController::registerSubject(http_request& request)
{
    value body = request.extract_json().get();
    string code = body["code"].as_string();
    string name = body["name"].as_string();
    int credits = body["credits"].as_integer();

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