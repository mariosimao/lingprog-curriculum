#include <iostream>
#include <string>
#include <cpprest/http_listener.h>
#include <pqxx/pqxx>
#include "./src/Infrastructure/Persistence/SqlStudentRepository.h"
#include "./src/Infrastructure/Persistence/SqlSubjectRepository.h"
#include "./src/Infrastructure/HTTP/StudentHttpController.h"
// #include "./src/Infrastructure/HTTP/SubjectHttpController.h"

using namespace std;

void handleRequest(web::http::http_request request)
{
    string route = request.request_uri().path();
    string method = request.method();

    cout << "[" << method << "] " << route << endl;

    string connectionString = "host=localhost port=5432 dbname=my_curriculum user=my_curriculum password=password";
    pqxx::connection connection(connectionString.c_str());

    SqlStudentRepository studentRepository(connection);
    SqlSubjectRepository subjectRepository(connection);

    StudentHttpController studentController(studentRepository, subjectRepository);
    // SubjectHttpController subjectController(subjectRepository);

    try {
        if (route == "/student") {
            if (method == "POST") {
                studentController.registerStudent(request);
                return;
            }
        }

        request.reply(web::http::status_codes::NotFound);
    } catch(const std::exception& e) {
        request.reply(web::http::status_codes::InternalError);
    }

    return;
}

int main(int argc, char const *argv[])
{
    try {
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
    } catch(const std::exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
}
