#ifndef STUDENT_SEMESTER_H
#define STUDENT_SEMESTER_H
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ctime>
#include <string>
#include <vector>
#include "SubjectAttempt.h"

using namespace std;

class StudentSemester
{
    private:
        string _id;
        string _name;
        boost::gregorian::date _startDate;
        boost::gregorian::date _endDate;
        vector<SubjectAttempt> _subjects;
    public:
        StudentSemester(
            string id,
            string name,
            boost::gregorian::date startDate,
            boost::gregorian::date endDate
        );
        StudentSemester(
            string id,
            string name,
            boost::gregorian::date startDate,
            boost::gregorian::date endDate,
            vector<SubjectAttempt> subjectAttempts
        );
        string getId();
        string getName();
        boost::gregorian::date getStartDate();
        boost::gregorian::date getEndDate();
        vector<SubjectAttempt> getSubjectsAttempts();
        SubjectAttempt& findSubjectAttempt(string subjectId);
        bool attemptWithSubjectExists(string subjectId);
        void planSubjectAttempt(string attemptId, string subjectId);
        void addGrade(string subjectId, float grade);
        void addProfessor(string subjectId, string professorName);
};
#endif
