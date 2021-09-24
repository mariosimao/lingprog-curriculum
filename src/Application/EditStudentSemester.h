#ifndef EDIT_STUDENT_SEMESTER_H
#define EDIT_STUDENT_SEMESTER_H
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../Domain/IStudentRepository.h"

using namespace std;

class EditStudentSemester
{
    private:
        IStudentRepository& _studentRepository;
    public:
        EditStudentSemester(IStudentRepository& studentRepository);
        void execute(
            string studentId,
            string semesterId,
            string newName,
            boost::gregorian::date newStartDate,
            boost::gregorian::date newEndDate
        );
};
#endif
