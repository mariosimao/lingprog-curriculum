#include "DomainException.h"
#include "StudentSemester.h"

StudentSemester::StudentSemester(
    string id,
    string name,
    boost::gregorian::date startDate,
    boost::gregorian::date endDate
) {
    if (startDate > endDate) {
        throw DomainException("Semester should start before ending.");
    }

    this->_id = id;
    this->_name = name;
    this->_startDate = startDate;
    this->_endDate = endDate;
    this->_subjects = vector<SubjectAttempt>();
}

string StudentSemester::getId()
{
    return this->_id;
}

string StudentSemester::getName()
{
    return this->_name;
}

boost::gregorian::date StudentSemester::getStartDate()
{
    return this->_startDate;
}

boost::gregorian::date StudentSemester::getEndDate()
{
    return this->_endDate;
}

vector<SubjectAttempt> StudentSemester::getSubjectsAttempts()
{
    return this->_subjects;
}

SubjectAttempt& StudentSemester::findSubjectAttempt(string subjectId)
{
    for (SubjectAttempt& attempt: this->_subjects) {
        if (attempt.getSubject().getId() == subjectId) {
            return attempt;
        }
    }

    throw DomainException("Subject attempt not found");
}

void StudentSemester::planSubjectAttempt(string attemptId, Subject& subject)
{
    // TODO: avoid duplicate attempts

    SubjectAttempt attempt(attemptId, subject);

    this->_subjects.push_back(attempt);
}

void StudentSemester::addGrade(string subjectId, float grade)
{
    SubjectAttempt attempt = this->findSubjectAttempt(subjectId);

    attempt.addGrade(grade);
}

void StudentSemester::addProfessor(string subjectId, string professorName)
{
    SubjectAttempt attempt = this->findSubjectAttempt(subjectId);

    attempt.addProfessor(professorName);
}
