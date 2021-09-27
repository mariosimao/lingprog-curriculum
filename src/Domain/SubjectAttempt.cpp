#include <string>
#include "Subject.h"
#include "SubjectAttempt.h"

SubjectAttempt::SubjectAttempt(string id, string subjectId)
{
    this->_id = id;
    this->_professor = "";
    this->_grade = -1;
    this->_subjectId = subjectId;
}

SubjectAttempt::SubjectAttempt(
    string id,
    float grade,
    string professor,
    string subjectId
) {
    this->_id = id;
    this->_professor = professor;
    this->_grade = grade;
    this->_subjectId = subjectId;
}


string SubjectAttempt::getId()
{
    return this->_id;
}

string SubjectAttempt::getSubjectId()
{
    return this->_subjectId;
}

string SubjectAttempt::getProfessor()
{
    return this->_professor;
}

float SubjectAttempt::getGrade()
{
    return this->_grade;
}

void SubjectAttempt::changeProfessor(string professorName)
{
    this->_professor = professorName;
}

void SubjectAttempt::changeGrade(float grade)
{
    this->_grade = grade;
}
