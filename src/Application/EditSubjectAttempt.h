#ifndef EDIT_SUBJECT_ATTEMPT_H
#define EDIT_SUBJECT_ATTEMPT_H
#include <string>
#include "../Domain/IStudentRepository.h"

using namespace std;

class EditSubjectAttempt
{
    private:
        IStudentRepository& _studentRepository;
    public:
        EditSubjectAttempt(IStudentRepository& studentRepository);
        void execute(
            string studentId,
            string semesterId,
            string attemptId,
            string newProfessor,
            float newGrade
        );
};
#endif
