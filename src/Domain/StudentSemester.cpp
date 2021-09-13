#include "DomainException.h"
#include "StudentSemester.h"

StudentSemester::StudentSemester(
    string id,
    string name,
    time_t startDate,
    time_t endDate
) {
    if (startDate > endDate) {
        throw DomainException("Semester should start before ending.");
    }

    this->_id = id;
    this->_name = name;
    this->_startDate = startDate;
    this->_endDate = endDate;
}

string StudentSemester::getId()
{
    return this->_id;
}

string StudentSemester::getName()
{
    return this->_name;
}

time_t StudentSemester::getStartDate()
{
    return this->_startDate;
}

time_t StudentSemester::getEndDate()
{
    return this->_endDate;
}

vector<SubjectAttempt*> StudentSemester::getSubjectsAttempts()
{
    return this->_subjects;
}

SubjectAttempt* StudentSemester::findSubjectAttempt(string subjectId)
{
    for (SubjectAttempt* attempt: this->_subjects) {
        if (attempt->getSubject()->getId() == subjectId) {
            return attempt;
        }
    }

    return NULL;
}

void StudentSemester::planSubjectAttempt(string attemptId, Subject* subject)
{
    SubjectAttempt* searchedAttempt = this->findSubjectAttempt(subject->getId());
    if (searchedAttempt != NULL) {
        throw DomainException("Cannot add subject on same semester twice.");
    }

    SubjectAttempt attempt(attemptId, subject);

    this->_subjects.push_back(&attempt);
}

void StudentSemester::addGrade(string subjectId, float grade)
{
    SubjectAttempt* attempt = this->findSubjectAttempt(subjectId);
    if (attempt == NULL) {
        throw DomainException("Subject is not planned on this semester.");
    }

    attempt->addGrade(grade);
}

void StudentSemester::addProfessor(string subjectId, string professorName)
{
    SubjectAttempt* attempt = this->findSubjectAttempt(subjectId);
    if (attempt == NULL) {
        throw DomainException("Subject is not planned on this semester.");
    }

    attempt->addProfessor(professorName);
}
