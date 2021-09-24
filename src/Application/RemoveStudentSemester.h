#ifndef REMOVE_STUDENT_SEMESTER_H
#define REMOVE_STUDENT_SEMESTER_H
#include <string>
#include "../Domain/IStudentRepository.h"

using namespace std;

class RemoveStudentSemester
{
    private:
        IStudentRepository& _studentRepository;
    public:
        RemoveStudentSemester(IStudentRepository& studentRepository);
        void execute(string studentId, string semesterId);
};
#endif
