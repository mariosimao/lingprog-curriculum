#ifndef SUBJECT_HTTP_CONTROLLER_H
#define SUBJECT_HTTP_CONTROLLER_H
#include <string>
#include <cpprest/http_listener.h>
#include "../../Domain/ISubjectRepository.h"

using namespace std;
namespace http = web::http;

class SubjectHttpController
{
    private:
        ISubjectRepository& _subjectRepository;
    public:
        SubjectHttpController(ISubjectRepository& subjectRepository);
        void registerSubject(http::http_request& request);
};
#endif
