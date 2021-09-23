#include <iostream>
#include <vector>
#include <string>
#include <pqxx/pqxx>
#include "./src/Infrastructure/Persistence/SqlStudentRepository.h"
#include "./src/Infrastructure/Persistence/SqlSubjectRepository.h"
#include "./src/Infrastructure/CLI/StudentCliController.h"
#include "./src/Infrastructure/CLI/SubjectCliController.h"
#include "./src/Domain/DomainException.h"

using namespace std;

int main(int argc, char const *argv[])
{
    try {
        string connectionString = "host=localhost port=5432 dbname=my_curriculum user=my_curriculum password=password";
        pqxx::connection connection(connectionString.c_str());

        SqlStudentRepository studentRepository(connection);
        SqlSubjectRepository subjectRepository(connection);

        StudentCliController studentController(studentRepository, subjectRepository);
        SubjectCliController subjectController(subjectRepository);

        if (argc < 2) {
            throw runtime_error("Too few arguments");
        }
        vector<string> arguments(argv, argv + argc);
        string command = arguments[1];
        arguments.erase(arguments.begin());
        arguments.erase(arguments.begin());

        if (command == "register-subject") {
            subjectController.registerSubject(arguments);
        } else if (command == "add-prerequisite") {
            subjectController.addPrerequisite(arguments);
        } else if (command == "register-student") {
            studentController.registerStudent(arguments);
        } else if (command == "plan-semester") {
            studentController.planSemester(arguments);
        } else if (command == "plan-subject") {
            studentController.planSubjectAttempt(arguments);
        }
    } catch (DomainException e) {
        cerr << e.what() << "\n";
        return 1;
    } catch (runtime_error &e) {
        cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
