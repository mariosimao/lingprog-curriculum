#ifndef STUDENT_H
#define STUDENT_H
#include <ctime>
#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "StudentSemester.h"

using namespace std;

class Student
{
    private:
        string _id;
        vector<StudentSemester> _semesters;
        void checkSemesterPeriod(
            date newStartDate,
            date newEndDate,
            string semesterId = ""
        );
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
        void editSemester(
            string semesterId,
            string newName,
            boost::gregorian::date newStartDate,
            boost::gregorian::date newEndDate
        );
        void removeSemester(string semesterId);
        void planSubjectAttempt(string attemptId, string semesterId, string subjectId);
        void removeSubjectAttempt(string semesterId, string attemptId);
        void addGrade(string semesterId, string subjectId, float grade);
        void addProfessor(string semesterId, string subjectId, string professor);
};
#endif
