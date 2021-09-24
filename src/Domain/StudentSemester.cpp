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

StudentSemester::StudentSemester(
    string id,
    string name,
    boost::gregorian::date startDate,
    boost::gregorian::date endDate,
    vector<SubjectAttempt> subjectAttempts
) {
    this->_id = id;
    this->_name = name;
    this->_startDate = startDate;
    this->_endDate = endDate;
    this->_subjects = subjectAttempts;
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
        if (attempt.getSubjectId() == subjectId) {
            return attempt;
        }
    }

    throw DomainException("Subject attempt not found");
}

bool StudentSemester::attemptWithSubjectExists(string subjectId)
{
    for (SubjectAttempt attempt: this->_subjects) {
        if (attempt.getSubjectId() == subjectId) {
            return true;
        }
    }

    return false;
}

void StudentSemester::planSubjectAttempt(string attemptId, string subjectId)
{
    if (this->attemptWithSubjectExists(subjectId)) {
        throw DomainException("A subject can not be attempted twice on a semester.");
    }

    SubjectAttempt attempt(attemptId, subjectId);

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
