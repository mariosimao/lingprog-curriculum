#ifndef LIST_SUBJECT_ATTEMPTS_BY_SEMESTER_H
#define LIST_SUBJECT_ATTEMPTS_BY_SEMESTER_H
#include <vector>
#include "Views/SubjectAttemptView.h"
#include "../Domain/IStudentRepository.h"

using namespace std;

class ListSubjectAttemptsBySemester
{
    private:
        IStudentRepository& _studentRepository;
    public:
        ListSubjectAttemptsBySemester(IStudentRepository& studentRepository);
        vector<SubjectAttemptView> execute(
            string studentId,
            string semesterId
        );
};
#endif
