#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "PlanSemester.h"
#include "../Domain/Student.h"

PlanSemester::PlanSemester(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

string PlanSemester::execute(
    string studentId,
    boost::gregorian::date startDate,
    boost::gregorian::date endDate
) {
    Student student = this->_studentRepository.findById(studentId);

    string id = boost::uuids::to_string(boost::uuids::random_generator()());
    student.planSemester(id, startDate, endDate);

    this->_studentRepository.save(student);

    return id;
}
