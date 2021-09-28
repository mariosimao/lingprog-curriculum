#include <pqxx/pqxx>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "./../../Domain/Student.h"
#include "./../../Domain/SubjectAttempt.h"
#include "SqlStudentRepository.h"

using namespace std;

SqlStudentRepository::SqlStudentRepository(
    pqxx::connection& connection
): _connection(connection)
{}

Student SqlStudentRepository::findById(string studentId)
{
    this->_connection.prepare(
        "find_student",
        "SELECT \
            s.id \
        FROM student s \
        WHERE s.id = $1"
    );

    this->_connection.prepare(
        "find_student_semesters",
        "SELECT \
            ss.id, \
            ss.name, \
            TO_CHAR(ss.start_date, 'YYYY-MM-DD'), \
            TO_CHAR(ss.end_date, 'YYYY-MM-DD') \
        FROM student_semester ss \
        WHERE ss.student_id = $1 \
        ORDER BY ss.start_date ASC"
    );

    this->_connection.prepare(
        "find_student_subjects",
        "SELECT \
            sa.id, \
            sa.semester_id, \
            sa.subject_id, \
            COALESCE(sa.grade, -1), \
            COALESCE(sa.professor, '') \
        FROM subject_attempt sa \
        JOIN student_semester ss ON ss.id = sa.semester_id \
        WHERE ss.student_id = $1"
    );

    pqxx::work transaction{this->_connection};

    pqxx::result studentResult  = transaction.exec_prepared("find_student", studentId);
    pqxx::result semesterResult = transaction.exec_prepared("find_student_semesters", studentId);
    pqxx::result attemptResult  = transaction.exec_prepared("find_student_subjects", studentId);

    if (studentResult.size() == 0) {
        throw runtime_error("Student not found");
    }

    vector<StudentSemester> semesters;
    for (auto row: semesterResult) {
        string semesterId(row[0].c_str());

        vector<SubjectAttempt> attempts;
        for (auto attemptRow: attemptResult) {
            string attemptSemesterId(attemptRow[1].c_str());

            if (attemptSemesterId == semesterId) {
                SubjectAttempt attempt(
                    attemptRow[0].c_str(),
                    stof(attemptRow[3].c_str()),
                    attemptRow[4].c_str(),
                    attemptRow[2].c_str()
                );
                attempts.push_back(attempt);
            }
        }

        StudentSemester semester(
            row[0].c_str(),
            row[1].c_str(),
            boost::gregorian::from_simple_string(row[2].c_str()),
            boost::gregorian::from_simple_string(row[3].c_str()),
            attempts
        );

        semesters.push_back(semester);
    }

    Student student(
        studentResult[0][0].c_str(),
        semesters
    );

    return student;
}

void SqlStudentRepository::save(Student& student)
{
    this->_connection.prepare(
        "save_student",
        "INSERT INTO student (id) \
        VALUES ($1) \
        ON CONFLICT DO NOTHING;"
    );

    this->_connection.prepare(
        "upsert_student_semester",
        "INSERT INTO student_semester (id, student_id, name, start_date, end_date) \
        VALUES ( \
            $1, \
            $2, \
            $3, \
            TO_DATE($4, 'YYYY-MM-DD'), \
            TO_DATE($5, 'YYYY-MM-DD') \
        ) \
        ON CONFLICT ON CONSTRAINT student_semester_pk DO \
        UPDATE SET \
        name = $3, \
        start_date = TO_DATE($4, 'YYYY-MM-DD'), \
        end_date = TO_DATE($5, 'YYYY-MM-DD') \
        WHERE student_semester.id = $1;"
    );

    this->_connection.prepare(
        "upsert_student_subject",
        "INSERT INTO subject_attempt (id, semester_id, subject_id, professor, grade) \
        VALUES ( \
            $1, \
            $2, \
            $3, \
            CASE WHEN $4 = '' THEN NULL ELSE $4 END, \
            CASE WHEN $5::FLOAT = -1 THEN NULL ELSE $5::FLOAT END \
        ) \
        ON CONFLICT ON CONSTRAINT subject_attempt_pK DO \
        UPDATE SET \
        semester_id = $2, \
        subject_id = $3, \
        professor = CASE WHEN $4 = '' THEN NULL ELSE $4 END, \
        grade = CASE WHEN $5::FLOAT = -1 THEN NULL ELSE $5::FLOAT END \
        WHERE subject_attempt.id = $1;"
    );

    pqxx::work transaction{this->_connection};

    try {
        transaction.exec_prepared(
            "save_student",
            student.getId()
        );

        string semestersIds;
        for (auto semester: student.getStudentSemesters()) {
            if (semestersIds.empty()) {
                semestersIds = "'" + transaction.esc(semester.getId()) + "'";
            } else {
                semestersIds += ", '" + transaction.esc(semester.getId()) + "'";
            }

            transaction.exec_prepared(
                "upsert_student_semester",
                semester.getId(),
                student.getId(),
                semester.getName(),
                boost::gregorian::to_iso_extended_string(semester.getStartDate()),
                boost::gregorian::to_iso_extended_string(semester.getEndDate())
            );

            string attemptsIds;
            for (auto attempt: semester.getSubjectsAttempts()) {
                if (attemptsIds.empty()) {
                    attemptsIds = "'" + transaction.esc(attempt.getId()) + "'";
                } else {
                    attemptsIds += ", '" + transaction.esc(attempt.getId()) + "'";
                }

                transaction.exec_prepared(
                    "upsert_student_subject",
                    attempt.getId(),
                    semester.getId(),
                    attempt.getSubjectId(),
                    attempt.getProfessor(),
                    to_string(attempt.getGrade())
                );
            }

            if (attemptsIds.empty()) {
                transaction.exec(
                    "DELETE FROM subject_attempt \
                    WHERE semester_id = '" + transaction.esc(semester.getId()) + "';"
                );
            } else {
                transaction.exec(
                    "DELETE FROM subject_attempt \
                    WHERE semester_id = '" + transaction.esc(semester.getId()) + "' \
                    AND id NOT IN (" + attemptsIds + ");"
                );
            }
        }

        if (!semestersIds.empty()) {
            transaction.exec(
                "DELETE FROM student_semester "
                "WHERE student_id = '" + transaction.esc(student.getId()) + "' " +
                "AND id NOT IN (" + semestersIds + ");"
            );
        } else {
            transaction.exec(
                "DELETE FROM student_semester "
                "WHERE student_id = '" + transaction.esc(student.getId()) + "';"
            );
        }

    } catch(pqxx::failure const &e) {
        transaction.abort();

        throw e;
    }

    transaction.commit();
}

void SqlStudentRepository::remove(string studentId)
{

}
