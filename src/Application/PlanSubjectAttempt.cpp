#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "PlanSubjectAttempt.h"
#include "../Domain/Student.h"
#include "../Domain/StudentSemester.h"
#include "../Domain/Subject.h"

PlanSubjectAttempt::PlanSubjectAttempt(
    IStudentRepository* studentRepository,
    ISubjectRepository* subjectRepository
) {
    this->_studentRepository = studentRepository;
    this->_subjectRepository = subjectRepository;
}

string PlanSubjectAttempt::execute(
    string studentId,
    string semesterId,
    string subjectId
) {
    Student student = this->_studentRepository->findById(studentId);
    Subject* subject = this->_subjectRepository->findById(subjectId);

    string id = boost::uuids::to_string(boost::uuids::random_generator()());
    student.planSubjectAttempt(id, semesterId, subject);

    this->_studentRepository->save(student);

    return id;
}
