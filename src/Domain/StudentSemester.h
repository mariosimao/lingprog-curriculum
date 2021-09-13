#ifndef STUDENT_SEMESTER_H
#define STUDENT_SEMESTER_H
#include <ctime>
#include <string>
#include <vector>
#include "Subject.h"
#include "SubjectAttempt.h"

using namespace std;

class StudentSemester
{
    private:
        string _id;
        string _name;
        time_t _startDate;
        time_t _endDate;
        vector<SubjectAttempt*> _subjects;
    public:
        StudentSemester(
            string id,
            string name,
            time_t startDate,
            time_t endDate
        );
        string getId();
        string getName();
        time_t getStartDate();
        time_t getEndDate();
        vector<SubjectAttempt*> getSubjectsAttempts();
        SubjectAttempt* findSubjectAttempt(string subjectId);
        void planSubjectAttempt(string attemptId, Subject* subject);
        void addGrade(string subjectId, float grade);
        void addProfessor(string subjectId, string professorName);
};
#endif
