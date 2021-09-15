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
        string _name;
        string _curriculumId;
        vector<StudentSemester*> _semesters;
    public:
        Student(string id, string name, string curriculumId);
        Student(
            string id,
            string name,
            string curriculumId,
            vector<StudentSemester*> semesters
        );
        string getId();
        string getName();
        string getCurriculumId();
        vector<StudentSemester*> getStudentSemesters();
        StudentSemester* findStudentSemester(string semesterId);
        void planSemester(
            string semesterId,
            string name,
            boost::gregorian::date startDate,
            boost::gregorian::date endDate
        );
        void planSubjectAttempt(string attemptId, string semesterId, Subject* subject);
        void addGrade(string semesterId, string subjectId, float grade);
        void addProfessor(string semesterId, string subjectId, string professor);
};
#endif
