#include "RemoveSubjectAttempt.h"
#include "../Domain/Student.h"
#include "../Domain/StudentSemester.h"
#include "../Domain/Subject.h"

RemoveSubjectAttempt::RemoveSubjectAttempt(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

void RemoveSubjectAttempt::execute(string studentId, string semesterId, string attemptId)
{
    Student student = this->_studentRepository.findById(studentId);

    student.removeSubjectAttempt(semesterId, attemptId);

    this->_studentRepository.save(student);

    return;
}
