#ifndef PLAN_SUBJECT_ATTEMPT_H
#define PLAN_SUBJECT_ATTEMPT_H
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../Domain/IStudentRepository.h"
#include "../Domain/ISubjectRepository.h"

using namespace std;

class PlanSubjectAttempt
{
    private:
        IStudentRepository& _studentRepository;
    public:
        PlanSubjectAttempt(IStudentRepository& studentRepository);
        string execute(
            string studentId,
            string semesterId,
            string subjectId
        );
};
#endif
