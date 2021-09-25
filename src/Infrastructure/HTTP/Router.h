#ifndef ROUTER_H
#define ROUTER_H
#include <cpprest/http_listener.h>
#include "StudentHttpController.h"
#include "SubjectHttpController.h"

using namespace std;
using namespace web::http;

class Router
{
    public:
        static http_response map(
            http_request request,
            StudentHttpController& studentController,
            SubjectHttpController& subjectController
        );
};
#endif
