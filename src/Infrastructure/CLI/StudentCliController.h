#ifndef STUDENT_CLI_CONTROLLER_H
#define STUDENT_CLI_CONTROLLER_H
#include <string>
#include <vector>
#include "../../Domain/IStudentRepository.h"
#include "../../Domain/ISubjectRepository.h"

using namespace std;

class StudentCliController
{
    private:
        IStudentRepository* _studentRepository;
        ISubjectRepository* _subjectRepository;
    public:
        StudentCliController(
            IStudentRepository* studentRepository,
            ISubjectRepository* subjectRepository
        );
        void registerStudent(vector<string> arguments);
        void planSemester(vector<string> arguments);
        void planSubjectAttempt(vector<string> arguments);
};
#endif
