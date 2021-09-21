#include <string>
#include "Subject.h"
#include "SubjectAttempt.h"

SubjectAttempt::SubjectAttempt(string id, Subject* subject)
{
    this->_id = id;
    this->_subject = subject;
    this->_professor = "";
    this->_grade = -1;
}

string SubjectAttempt::getId()
{
    return this->_id;
}

Subject* SubjectAttempt::getSubject()
{
    return this->_subject;
}

string SubjectAttempt::getProfessor()
{
    return this->_professor;
}

float SubjectAttempt::getGrade()
{
    return this->_grade;
}

void SubjectAttempt::addProfessor(string professorName)
{
    this->_professor = professorName;
}

void SubjectAttempt::addGrade(float grade)
{
    this->_grade = grade;
}
