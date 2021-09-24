#include <boost/date_time/gregorian/gregorian.hpp>

#include "ListStudentSemesters.h"
#include "../Domain/Student.h"

ListStudentSemesters::ListStudentSemesters(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

vector<StudentSemesterView> ListStudentSemesters::execute(string studentId)
{
    Student student = this->_studentRepository.findById(studentId);

    vector<StudentSemesterView> semesters;
    for (auto semester: student.getStudentSemesters()) {
        StudentSemesterView view {
            semester.getId(),
            semester.getName(),
            boost::gregorian::to_iso_extended_string(semester.getStartDate()),
            boost::gregorian::to_iso_extended_string(semester.getEndDate())
        };

        semesters.push_back(view);
    }

    return semesters;
}
