#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "PlanSemester.h"
#include "../Domain/Student.h"

PlanSemester::PlanSemester(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

StudentSemesterView PlanSemester::execute(
    string studentId,
    boost::gregorian::date startDate,
    boost::gregorian::date endDate
) {
    Student student = this->_studentRepository.findById(studentId);

    string id = boost::uuids::to_string(boost::uuids::random_generator()());
    student.planSemester(id, startDate, endDate);
    StudentSemester semester = student.findStudentSemester(id);

    this->_studentRepository.save(student);

    return StudentSemesterView {
        semester.getId(),
        semester.getName(),
        boost::gregorian::to_iso_extended_string(semester.getStartDate()),
        boost::gregorian::to_iso_extended_string(semester.getEndDate())
    };
}
