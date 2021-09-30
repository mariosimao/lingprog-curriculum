#include <iostream>
#include <string>
#include <vector>

#include <cpprest/http_listener.h>
#include <pqxx/pqxx>

#include "./src/Domain/DomainException.h"
#include "./src/Infrastructure/Persistence/SqlStudentRepository.h"
#include "./src/Infrastructure/Persistence/SqlSubjectRepository.h"
#include "./src/Infrastructure/HTTP/Router.h"
#include "./src/Infrastructure/HTTP/StudentHttpController.h"
#include "./src/Infrastructure/HTTP/SubjectHttpController.h"

using namespace std;
using namespace web::http;
using namespace web::json;

void handleRequest(http_request request)
{
    string route = request.request_uri().path();
    vector<string> path = uri::split_path(route);
    string method = request.method();

    cout << "[" << method << "] " << route << endl;

    http_response response;
    try {
        string connectionString = "host=kesavan.db.elephantsql.com port=5432 dbname=zmtyiekd user=zmtyiekd password=M9Ak4_OZOTwjWt_A6AvNFx87uGc2_f7q";
        pqxx::connection connection(connectionString.c_str());

        SqlStudentRepository studentRepository(connection);
        SqlSubjectRepository subjectRepository(connection);

        StudentHttpController studentController(studentRepository, subjectRepository);
        SubjectHttpController subjectController(subjectRepository);

        response = Router::map(request, studentController, subjectController);
    } catch (json_exception& e) {
        value body = value::object();
        body["error"] = value::object();
        body["error"]["message"] = value::string("Invalid request body.");

        response.set_body(body);
        response.set_status_code(status_codes::BadRequest);
    } catch(DomainException& e) {
        value body = value::object();
        body["error"] = value::object();
        body["error"]["message"] = value::string(e.what());

        response.set_body(body);
        response.set_status_code(status_codes::BadRequest);
    } catch(std::exception& e) {
        cerr << e.what() << endl;
        value body = value::object();
        body["error"] = value::object();
        body["error"]["message"] = value::string("Internal error.");

        response.set_body(body);
        response.set_status_code(status_codes::InternalError);
    }

    response.headers().add("Access-Control-Allow-Origin", "*");
    response.headers().add("Access-Control-Allow-Headers", "*");
    response.headers().add("Access-Control-Allow-Methods", "*");

    request.reply(response);
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
    uri uri(address);

    experimental::listener::http_listener httpListener(uri);

    httpListener.support(methods::OPTIONS, handleRequest);
    httpListener.support(handleRequest);

    httpListener.open().wait();
    cout << "Listening on " << address << endl;
    cout << "Press ENTER to exit." << endl;

    string line;
    getline(cin, line);

    httpListener.close();
    return 0;
}
