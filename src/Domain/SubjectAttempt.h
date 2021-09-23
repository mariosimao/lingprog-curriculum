#ifndef SUBJECT_ATTEMPT_H
#define SUBJECT_ATTEMPT_H
#include <string>
#include "Subject.h"

using namespace std;

class SubjectAttempt
{
    private:
        string _id;
        string _professor;
        float _grade;
        Subject& _subject;
    public:
        SubjectAttempt(string id, Subject& subject);
        string getId();
        Subject getSubject();
        string getProfessor();
        float getGrade();
        void addProfessor(string professorName);
        void addGrade(float grade);
};
#endif