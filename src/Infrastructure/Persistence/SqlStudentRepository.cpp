#include <pqxx/pqxx>
#include <iostream>
#include "./../../Domain/Student.h"
#include "SqlStudentRepository.h"

using namespace std;

SqlStudentRepository::SqlStudentRepository(
    pqxx::connection* connection
) {
    this->_connection = connection;
    // this->_subjectRepository = subjectRepository;
}

Student SqlStudentRepository::findById(string studentId)
{
    this->_connection->prepare(
        "find_student",
        "SELECT \
            s.name, \
            s.curriculum_id \
        FROM student s \
        WHERE s.id = $1"
    );

    this->_connection->prepare(
        "find_student_semesters",
        "SELECT \
            ss.id, \
            ss.name, \
            ss.start_date, \
            ss.end_date \
        FROM student_semester ss \
        WHERE ss.student_id = $1"
    );

    this->_connection->prepare(
        "find_student_subjects",
        "SELECT \
            sa.id, \
            sa.subject_code, \
            sa.grade, \
            sa.professor \
        FROM subject_attempt sa \
        JOIN student_semester ss ON ss.id = sa.semester_id \
        WHERE ss.student_id = $1"
    );

    pqxx::work transaction{*this->_connection};

    pqxx::result studentResult  = transaction.exec_prepared("find_student", studentId);
    // pqxx::result semesterResult = transaction.exec_prepared("find_student_semesters", studentId);
    // pqxx::result attemptResult  = transaction.exec_prepared("find_student_subjects", studentId);

    if (studentResult.size() == 0) {
        throw runtime_error("Student not found");
    }

    Student student(
        studentId,
        studentResult[0][0].c_str(),
        studentResult[0][1].c_str()
    );

    return student;
}

void SqlStudentRepository::save(Student student)
{
    this->_connection->prepare(
        "save_student",
        "INSERT INTO student (id, name, curriculum_id) \
        VALUES ($1, $2, $3) \
        ON CONFLICT ON CONSTRAINT student_pk DO \
        UPDATE SET \
        name = $2, \
        curriculum_id = $3 \
        WHERE student.id = $1;"
    );

    this->_connection->prepare(
        "upsert_student_semester",
        "INSERT INTO student_semester (id, student_id, name, start_date, end_date) \
        VALUES ($1, $2, $3, $4, $5) \
        ON CONFLICT DO \
        UPDATE SET \
        name = $3, \
        start_date = $4, \
        end_date = $5 \
        WHERE id = $1;"
    );

    this->_connection->prepare(
        "upsert_student_subject",
        "INSERT INTO subject_attempt (id, semester_id, subject_code, professor, grade) \
        VALUES ($1, $2, $3, $4, $5) \
        ON CONFLICT DO \
        UPDATE SET \
        semester_id = $2, \
        subject_code = $3, \
        professor = $4, \
        grade = $5 \
        WHERE id = $1;"
    );

    pqxx::work transaction{*this->_connection};

    try {
        transaction.exec_prepared(
            "save_student",
            student.getId(),
            student.getName(),
            student.getCurriculumId()
        );

        /*
        string semestersIds;
        for (auto semester: student.getStudentSemesters()) {
            if (semestersIds.empty()) {
                semestersIds = transaction.esc(semester->getId());
            } else {
                semestersIds += ", " + transaction.esc(semester->getId());
            }

            transaction.exec_prepared(
                "upsert_student_semester",
                semester->getId(),
                student.getId(),
                semester->getName(),
                semester->getStartDate(),
                semester->getEndDate()
            );

            string attemptsIds;
            for (auto attempt: semester->getSubjectsAttempts()) {
                if (attemptsIds.empty()) {
                    attemptsIds = transaction.esc(attempt->getId());
                } else {
                    attemptsIds += ", " + transaction.esc(attempt->getId());
                }

                transaction.exec_prepared(
                    "upsert_student_subject",
                    attempt->getId(),
                    semester->getId(),
                    attempt->getSubjectCode(),
                    attempt->getGrade(),
                    attempt->getProfessor()
                );
            }

            transaction.exec(
                "DELETE subject_attempt sa \
                WHERE sa.semester_id IN ( \
                    SELECT id \
                    FROM student_semester \
                    WHERE student_id = $1 \
                ) AND NOT IN (" + attemptsIds + ");"
            );
        }

        transaction.exec(
            "DELETE student_semester ss "
            "WHERE ss.student_id = " + transaction.esc(student.getId()) +
            "AND ss.id NOT IN (" + semestersIds + ");"
        );*/
    } catch(pqxx::failure const &e) {
        transaction.abort();

        throw e;
    }

    transaction.commit();
}

void SqlStudentRepository::remove(string studentId)
{

}
