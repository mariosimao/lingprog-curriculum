#include "DomainException.h"
#include "StudentSemester.h"

StudentSemester::StudentSemester(
    string id,
    string name,
    date startDate,
    date endDate
) {
    this->checkPeriod(startDate, endDate);

    this->_id = id;
    this->_name = name;
    this->_startDate = startDate;
    this->_endDate = endDate;
    this->_subjects = vector<SubjectAttempt>();
}

StudentSemester::StudentSemester(
    string id,
    string name,
    date startDate,
    date endDate,
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

date StudentSemester::getStartDate()
{
    return this->_startDate;
}

date StudentSemester::getEndDate()
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

SubjectAttempt& StudentSemester::findSubjectAttemptById(string attemptId)
{
    for (SubjectAttempt& attempt: this->_subjects) {
        if (attempt.getId() == attemptId) {
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

void StudentSemester::rename(string newName)
{
    this->_name = newName;
}

void StudentSemester::changeDates(date newStartDate, date newEndDate)
{
    this->checkPeriod(newStartDate, newEndDate);

    this->_startDate = newStartDate;
    this->_endDate = newEndDate;
}

void StudentSemester::planSubjectAttempt(string attemptId, string subjectId)
{
    if (this->attemptWithSubjectExists(subjectId)) {
        throw DomainException("A subject can not be attempted twice on a semester.");
    }

    SubjectAttempt attempt(attemptId, subjectId);

    this->_subjects.push_back(attempt);
}

void StudentSemester::removeSubjectAttempt(string attemptId)
{
    this->_subjects.erase(
        remove_if(
            this->_subjects.begin(),
            this->_subjects.end(),
            [attemptId](SubjectAttempt attempt) {
                return attempt.getId() == attemptId;
            }
        ),
        this->_subjects.end()
    );

    return;
}

void StudentSemester::changeGrade(string attemptId, float grade)
{
    SubjectAttempt& attempt = this->findSubjectAttemptById(attemptId);

    attempt.changeGrade(grade);
}

void StudentSemester::changeProfessor(string attemptId, string professorName)
{
    SubjectAttempt& attempt = this->findSubjectAttemptById(attemptId);

    attempt.changeProfessor(professorName);
}

void StudentSemester::checkPeriod(date newStartDate, date newEndDate)
{
    if (newStartDate > newEndDate) {
        throw DomainException("Semester should start before ending.");
    }

    return;
}
