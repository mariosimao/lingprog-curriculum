#include <pqxx/pqxx>
#include "./../../Domain/Student.h"
#include "SqlStudentRepository.h"

using namespace std;

void SqlStudentRepository::save(Student student)
{
    string query = R""""(
        INSERT INTO student (id, name, curriculum_id)
        VALUES ($1, $2, $3)
        ON CONFLICT DO
        UPDATE student s (name, curriculum_id) WHERE s.id = $1;
    )"""";

    student.getId();
    student.getName();
    student.getCurriculumId();
    auto semesters = student.getStudentSemesters();
    for (auto semester: semesters) {
        semester->getId();
        semester->getName();
        semester->getStartDate();
        semester->getEndDate();
        auto attempts = semester->getSubjectsAttempts();
    }

    student
        -> id
        -> name
        -> curriculum_id
        -> semesters
            -> id
            -> name
            -> start date
            -> end date
            -> subject attempt
                -> id
                -> subject code
                -> professor
                -> grade

    "
    INSERT INTO student_semester (id, student_id, name, start_date, end_date)
    VALUES ($1, $2, $3, $4, $5)
    ON CONFLICT DO
    UPDATE student_semester ss (name, start_date, end_date)
    WHERE ss.id = $1;
    ";

    "
    DELETE student_semester ss
    WHERE ss.student_id = $1
    AND ss.id NOT IN (...);
    ";

    "
    INSERT INTO subject_attempt (semester_id, subject_code, professor, grade)
    VALUES ($1, $2, $3, $4)
    ON CONFLICT DO
    UPDATE subject_attempt sa
    WHERE sa.semester_id = $1 AND sa.subject_code = $2;
    ";

    "DELETE subject_attempt sa
    WHERE sa.semester_id IN (
        SELECT id
        FROM student_semester
        WHERE student_id = $1
    ) AND NOT IN (...)";
}
