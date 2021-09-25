#ifndef SUBJECT_HTTP_CONTROLLER_H
#define SUBJECT_HTTP_CONTROLLER_H
#include <string>
#include <cpprest/http_listener.h>
#include "../../Domain/ISubjectRepository.h"

using namespace std;
using namespace web::http;

class SubjectHttpController
{
    private:
        ISubjectRepository& _subjectRepository;
    public:
        SubjectHttpController(ISubjectRepository& subjectRepository);
        http_response registerSubject(http_request& request);
};
#endif
