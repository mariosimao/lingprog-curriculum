#ifndef STUDENT_H
#define STUDENT_H
#include <ctime>
#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "Subject.h"
#include "StudentSemester.h"

using namespace std;

class Student
{
    private:
        string _id;
        vector<StudentSemester> _semesters;
    public:
        Student(string id);
        Student(
            string id,
            vector<StudentSemester> semesters
        );
        string getId();
        vector<StudentSemester> getStudentSemesters();
        StudentSemester& findStudentSemester(string semesterId);
        void planSemester(
            string semesterId,
            boost::gregorian::date startDate,
            boost::gregorian::date endDate
        );
        void planSubjectAttempt(string attemptId, string semesterId, Subject& subject);
        void addGrade(string semesterId, string subjectId, float grade);
        void addProfessor(string semesterId, string subjectId, string professor);
};
#endif
