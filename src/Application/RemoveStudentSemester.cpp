#include "RemoveStudentSemester.h"
#include "../Domain/Student.h"
#include "../Domain/StudentSemester.h"
#include "../Domain/Subject.h"

RemoveStudentSemester::RemoveStudentSemester(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

void RemoveStudentSemester::execute(string studentId, string semesterId)
{
    Student student = this->_studentRepository.findById(studentId);

    student.removeSemester(semesterId);

    this->_studentRepository.save(student);

    return;
}
