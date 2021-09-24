#ifndef LIST_STUDENT_SEMESTERS_H
#define LIST_STUDENT_SEMESTERS_H
#include <string>
#include "../Domain/IStudentRepository.h"

using namespace std;

struct StudentSemesterView {
    string id;
    string name;
    string startDate;
    string endDate;
};

class ListStudentSemesters
{
    private:
        IStudentRepository& _studentRepository;
    public:
        ListStudentSemesters(IStudentRepository& studentRepository);
        vector<StudentSemesterView> execute(string studentId);
};
#endif
