#ifndef STUDENT_HTTP_CONTROLLER_H
#define STUDENT_HTTP_CONTROLLER_H
#include <string>
#include <cpprest/http_listener.h>
#include <pqxx/pqxx>
#include "../../Domain/IStudentRepository.h"
#include "../../Domain/ISubjectRepository.h"

using namespace std;
namespace http = web::http;

class StudentHttpController
{
    private:
        IStudentRepository& _studentRepository;
        ISubjectRepository& _subjectRepository;
    public:
        StudentHttpController(
            IStudentRepository& studentRepository,
            ISubjectRepository& subjectRepository
        );
        void registerStudent(http::http_request& request);
        void listSemesters(http::http_request& request, string studentId);
        void planSemester(http::http_request& request, string studentId);
        void planSubjectAttempt(
            http::http_request& request,
            string studentId,
            string semesterId
        );
};
#endif
