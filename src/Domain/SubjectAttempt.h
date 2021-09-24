#ifndef SUBJECT_ATTEMPT_H
#define SUBJECT_ATTEMPT_H
#include <string>

using namespace std;

class SubjectAttempt
{
    private:
        string _id;
        string _professor;
        float _grade;
        string _subjectId;
    public:
        SubjectAttempt(string id, string subjectId);
        SubjectAttempt(string id, float grade, string professor, string subject);
        string getId();
        string getSubjectId();
        string getProfessor();
        float getGrade();
        void addProfessor(string professorName);
        void addGrade(float grade);
};
#endif