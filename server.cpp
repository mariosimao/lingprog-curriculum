#include <iostream>
#include <string>
#include <vector>

#include <cpprest/http_listener.h>
#include <pqxx/pqxx>

#include "./src/Domain/DomainException.h"
#include "./src/Infrastructure/Persistence/SqlStudentRepository.h"
#include "./src/Infrastructure/Persistence/SqlSubjectRepository.h"
#include "./src/Infrastructure/HTTP/StudentHttpController.h"
#include "./src/Infrastructure/HTTP/SubjectHttpController.h"

using namespace std;

void handleRequest(web::http::http_request request)
{
    string route = request.request_uri().path();
    vector<string> path = web::http::uri::split_path(route);
    string method = request.method();

    cout << "[" << method << "] " << route << endl;

    string connectionString = "host=localhost port=5432 dbname=my_curriculum user=my_curriculum password=password";
    pqxx::connection connection(connectionString.c_str());

    SqlStudentRepository studentRepository(connection);
    SqlSubjectRepository subjectRepository(connection);

    StudentHttpController studentController(studentRepository, subjectRepository);
    SubjectHttpController subjectController(subjectRepository);

    try {
        if (route == "/students") {
            if (method == "POST") {
                studentController.registerStudent(request);
                return;
            }
        }

        /* /student/:studentId/semester */
        if (path.size() == 3 &&
            path[0] == "students" &&
            path[2] == "semesters"
        ) {
            string studentId = path[1];

            if (method == "GET") {
                studentController.listSemesters(request, studentId);
                return;
            } else if (method == "POST") {
                studentController.planSemester(request, studentId);
                return;
            }
        }

        if (path.size() == 5 &&
            path[0] == "students" &&
            path[2] == "semesters" &&
            path[4] == "subject-attempts"
        ) {
            string studentId = path[1];
            string semesterId = path[3];

            if (method == "POST") {
                studentController.planSubjectAttempt(
                    request,
                    studentId,
                    semesterId
                );
                return;
            }
        }

        if (route == "/subjects") {
            if (method == "POST") {
                subjectController.registerSubject(request);
                return;
            }
        }

        request.reply(web::http::status_codes::NotFound);
    } catch (web::json::json_exception& e) {
        web::json::value response = web::json::value::object();
        response["error"] = web::json::value::object();
        response["error"]["message"] = web::json::value::string(
            "Invalid request body."
        );

        request.reply(web::http::status_codes::BadRequest, response);
    } catch(DomainException& e) {
        web::json::value response = web::json::value::object();
        response["error"] = web::json::value::object();
        response["error"]["message"] = web::json::value::string(e.what());

        request.reply(web::http::status_codes::BadRequest, response);
    } catch(std::exception& e) {
        cerr << e.what() << endl;
        web::json::value response = web::json::value::object();
        response["error"] = web::json::value::object();
        response["error"]["message"] = web::json::value::string(
            "Internal error."
        );

        request.reply(web::http::status_codes::InternalError, response);
    }

    return;
}

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cerr << "Missing arguments. Usage: server <address> <port>" << endl;
        return 1;
    }
    string address = string(argv[1]);
    string port = string(argv[2]);

    address.append(":");
    address.append(port);
    web::http::uri uri(address);

    web::http::experimental::listener::http_listener httpListener(uri);

    httpListener.support(handleRequest);

    httpListener.open().wait();
    cout << "Listening on " << address << endl;
    cout << "Press ENTER to exit." << endl;

    string line;
    getline(cin, line);

    httpListener.close();
    return 0;
}
