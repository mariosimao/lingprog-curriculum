#ifndef REGISTER_STUDENT_H
#define REGISTER_STUDENT_H
#include <string>
#include "../Domain/IStudentRepository.h"

using namespace std;

class RegisterStudent
{
    private:
        IStudentRepository& _studentRepository;
    public:
        RegisterStudent(IStudentRepository& studentRepository);
        string execute(string studentId);
};
#endif
