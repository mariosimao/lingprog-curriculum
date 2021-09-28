#include "EditSubjectAttempt.h"

EditSubjectAttempt::EditSubjectAttempt(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

void EditSubjectAttempt::execute(
    string studentId,
    string semesterId,
    string attemptId,
    string newProfessor,
    float newGrade,
    string newSemesterId
) {
    Student student = this->_studentRepository.findById(studentId);

    student.changeSubjectGrade(semesterId, attemptId, newGrade);
    student.changeSubjectProfessor(semesterId, attemptId, newProfessor);
    student.moveSubjectAttempt(semesterId, attemptId, newSemesterId);

    this->_studentRepository.save(student);

    return;
}
