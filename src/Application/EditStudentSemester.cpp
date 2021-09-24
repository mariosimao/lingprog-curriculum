#include "EditStudentSemester.h"
#include "../Domain/Student.h"
#include "../Domain/StudentSemester.h"
#include "../Domain/Subject.h"

EditStudentSemester::EditStudentSemester(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

void EditStudentSemester::execute(
    string studentId,
    string semesterId,
    string newName,
    boost::gregorian::date newStartDate,
    boost::gregorian::date newEndDate
) {
    Student student = this->_studentRepository.findById(studentId);

    student.editSemester(
        semesterId,
        newName,
        newStartDate,
        newEndDate
    );

    this->_studentRepository.save(student);

    return;
}
