#include "RegisterStudent.h"
#include "../Domain/Student.h"

RegisterStudent::RegisterStudent(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

string RegisterStudent::execute(string studentId)
{
    Student student(studentId);

    this->_studentRepository.save(student);

    return studentId;
}
