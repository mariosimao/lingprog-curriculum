#ifndef STUDENT_H
#define STUDENT_H
#include <ctime>
#include <string>
#include <vector>
// #include "Subject.h"
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
        Student(
            string id,
            string name,
            string curriculumId
        );
        string getId();
        string getName();
        string getCurriculumId();
        vector<StudentSemester*> getStudentSemesters();
        StudentSemester* findStudentSemester(string semesterId);
        void planSemester(
            string semesterId,
            string name,
            time_t startDate,
            time_t endDate
        );
        void planSubjectAttempt(string attemptId, string semesterId, Subject* subject);
        void addGrade(string semesterId, string subjectId, float grade);
        void addProfessor(string semesterId, string subjectId, string professor);
};
#endif