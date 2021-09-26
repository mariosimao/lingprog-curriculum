#ifndef STUDENT_HTTP_CONTROLLER_H
#define STUDENT_HTTP_CONTROLLER_H
#include <string>
#include <cpprest/http_listener.h>
#include <pqxx/pqxx>
#include "../../Domain/IStudentRepository.h"
#include "../../Domain/ISubjectRepository.h"

using namespace std;
using namespace web::http;

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
        http_response registerStudent(http_request& request);
        http_response listSemesters(http_request& request, string studentId);
        http_response planSemester(http_request& request, string studentId);
        http_response editSemester(
            http_request& request,
            string studentId,
            string semesterId
        );
        http_response removeSemester(
            http_request& request,
            string studentId,
            string semesterId
        );
        http_response listSubjectAttemptsBySemester(
            http_request& request,
            string studentId,
            string semesterId
        );
        http_response planSubjectAttempt(
            http_request& request,
            string studentId,
            string semesterId
        );
};
#endif
