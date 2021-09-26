#include <string>
#include <vector>
#include "Router.h"

using namespace web::json;

http_response Router::map(
    http_request request,
    StudentHttpController& studentController,
    SubjectHttpController& subjectController
) {
    string route = request.request_uri().path();
    vector<string> path = web::http::uri::split_path(route);
    string method = request.method();

    if (method == "OPTIONS") {
        return http_response(status_codes::OK);
    }

    if (route == "/students") {
        if (method == "POST") {
            return studentController.registerStudent(request);
        }
    }

    /* /student/:studentId/semester */
    if (path.size() == 3 &&
        path[0] == "students" &&
        path[2] == "semesters"
    ) {
        string studentId = path[1];

        if (method == "GET") {
            return studentController.listSemesters(request, studentId);
        } else if (method == "POST") {
            return studentController.planSemester(request, studentId);
        }
    }

    /* /students/:studentId/semesters/:semesterId */
    if (path.size() == 4 &&
        path[0] == "students" &&
        path[2] == "semesters"
    ) {
        string studentId = path[1];
        string semesterId = path[3];

        if (method == "PUT") {
            return studentController.editSemester(
                request,
                studentId,
                semesterId
            );
        } else if (method == "DELETE") {
            return studentController.removeSemester(
                request,
                studentId,
                semesterId
            );
        }
    }

    /* /students/:studentId/semesters/:semesterId/subject-attempts */
    if (path.size() == 5 &&
        path[0] == "students" &&
        path[2] == "semesters" &&
        path[4] == "subject-attempts"
    ) {
        string studentId = path[1];
        string semesterId = path[3];

        if (method == "POST") {
            return studentController.planSubjectAttempt(
                request,
                studentId,
                semesterId
            );
        }
    }

    if (route == "/subjects") {
        if (method == "GET") {
            return subjectController.listSubjects(request);
        } else if (method == "POST") {
            return subjectController.registerSubject(request);
        }
    }

    return http_response(status_codes::NotFound);
}