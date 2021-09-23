#ifndef I_STUDENT_REPOSITORY_H
#define I_STUDENT_REPOSITORY_H
#include "Student.h"

using namespace std;
class IStudentRepository
{
    public:
        ~IStudentRepository() {};
        virtual Student findById(string studentId) = 0;
        virtual void save(Student& student) = 0;
        virtual void remove(string studentId) = 0;
};
#endif
