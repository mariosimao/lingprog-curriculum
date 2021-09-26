#ifndef REMOVE_SUBJECT_ATTEMPT_H
#define REMOVE_SUBJECT_ATTEMPT_H
#include <string>
#include "../Domain/IStudentRepository.h"

using namespace std;

class RemoveSubjectAttempt
{
    private:
        IStudentRepository& _studentRepository;
    public:
        RemoveSubjectAttempt(IStudentRepository& studentRepository);
        void execute(string studentId, string semesterId, string attemptId);
};
#endif
