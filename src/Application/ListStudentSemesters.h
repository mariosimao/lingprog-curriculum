#ifndef LIST_STUDENT_SEMESTERS_H
#define LIST_STUDENT_SEMESTERS_H
#include <string>
#include "Views/StudentSemesterView.h"
#include "../Domain/IStudentRepository.h"

using namespace std;

class ListStudentSemesters
{
    private:
        IStudentRepository& _studentRepository;
    public:
        ListStudentSemesters(IStudentRepository& studentRepository);
        vector<StudentSemesterView> execute(string studentId);
};
#endif
