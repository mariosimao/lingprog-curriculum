#include "EditSubjectAttempt.h"

EditSubjectAttempt::EditSubjectAttempt(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

void EditSubjectAttempt::execute(
    string studentId,
    string semesterId,
    string attemptId,
    string newProfessor,
    float newGrade
) {
    Student student = this->_studentRepository.findById(studentId);

    student.changeGrade(semesterId, attemptId, newGrade);
    student.changeProfessor(semesterId, attemptId, newProfessor);

    this->_studentRepository.save(student);

    return;
}
