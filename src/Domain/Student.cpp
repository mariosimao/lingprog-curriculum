#include "DomainException.h"
#include "Student.h"

Student::Student(string id, string name, string curriculumId)
{
    this->_id = id;
    this->_name = name;
    this->_curriculumId = curriculumId;
}

Student::Student(
    string id,
    string name,
    string curriculumId,
    vector<StudentSemester*> semesters
) {
    this->_id = id;
    this->_name = name;
    this->_curriculumId = curriculumId;
    this->_semesters = semesters;
}

string Student::getId()
{
    return this->_id;
}

string Student::getName()
{
    return this->_name;
}

string Student::getCurriculumId()
{
    return this->_curriculumId;
}

vector<StudentSemester*> Student::getStudentSemesters()
{
    return this->_semesters;
}

StudentSemester* Student::findStudentSemester(string semesterId)
{
    for (StudentSemester* semester: this->_semesters) {
        if (semester->getId() == semesterId) {
            return semester;
        }
    }

    return NULL;
}

void Student::planSemester(
    string semesterId,
    string name,
    boost::gregorian::date startDate,
    boost::gregorian::date endDate
) {
    bool semesterExist = (this->findStudentSemester(semesterId) != NULL);
    if (semesterExist) {
        throw DomainException(string("Semester already exists."));
    }

    StudentSemester* semester = new StudentSemester(semesterId, name, startDate, endDate);

    this->_semesters.push_back(semester);
}

void Student::planSubjectAttempt(
    string attemptId,
    string semesterId,
    Subject* subject
) {
    StudentSemester* semester = this->findStudentSemester(semesterId);
    if (semester == NULL) {
        throw DomainException(string("Semester does not exist."));
    }

    semester->planSubjectAttempt(attemptId, subject);
}

void Student::addGrade(string semesterId, string subjectId, float grade)
{
    StudentSemester* semester = this->findStudentSemester(semesterId);
    if (semester == NULL) {
        throw DomainException(string("Semester does not exist."));
    }

    semester->addGrade(subjectId, grade);
}

void Student::addProfessor(string semesterId, string subjectId, string professor)
{
    StudentSemester* semester = this->findStudentSemester(semesterId);
    if (semester == NULL) {
        throw DomainException(string("Semester does not exist."));
    }

    semester->addProfessor(subjectId, professor);
}
