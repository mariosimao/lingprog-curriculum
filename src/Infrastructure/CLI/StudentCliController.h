#ifndef STUDENT_CLI_CONTROLLER_H
#define STUDENT_CLI_CONTROLLER_H
#include <string>
#include <vector>
#include "../../Domain/IStudentRepository.h"

using namespace std;

class StudentCliController
{
    private:
        IStudentRepository* _studentRepository;
    public:
        StudentCliController(IStudentRepository* studentRepository);
        void registerStudent(vector<string> arguments);
        void planSemester(vector<string> arguments);
};
#endif
