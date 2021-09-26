#include "ListSubjectAttemptsBySemester.h"
#include "../Domain/Student.h"

ListSubjectAttemptsBySemester::ListSubjectAttemptsBySemester(IStudentRepository& studentRepository):
    _studentRepository(studentRepository) {}

vector<SubjectAttemptView> ListSubjectAttemptsBySemester::execute(
    string studentId,
    string semesterId
) {
    Student student = this->_studentRepository.findById(studentId);

    vector<SubjectAttemptView> attempts;
    for (auto attempt: student.findStudentSemester(semesterId).getSubjectsAttempts()) {
        SubjectAttemptView view {
            attempt.getId(),
            attempt.getSubjectId(),
            attempt.getProfessor(),
            attempt.getGrade()
        };

        attempts.push_back(view);
    }

    return attempts;
}
