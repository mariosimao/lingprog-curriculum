#include <pqxx/pqxx>
#include <set>
#include <string>
#include "./../../Domain/DomainException.h"
#include "./../../Domain/Subject.h"
#include "SqlSubjectRepository.h"

using namespace std;

SqlSubjectRepository::SqlSubjectRepository(
    pqxx::connection& connection
): _connection(connection)
{}

Subject SqlSubjectRepository::findById(string subjectId)
{
    this->_connection.prepare(
        "find_subject",
        "SELECT \
            s.code, \
            s.name, \
            s.credits \
        FROM subject s \
        WHERE s.id = $1"
    );

    this->_connection.prepare(
        "find_subject_prerequisites",
        "SELECT \
            sp.prerequisite_id \
        FROM subject_prerequisite sp \
        WHERE sp.subject_id = $1"
    );

    this->_connection.prepare(
        "find_subject_corequisites",
        "SELECT \
            sc.corequisite_id \
        FROM subject_corequisite sc \
        WHERE sc.subject_id = $1"
    );

    pqxx::work transaction{this->_connection};

    pqxx::result subjectResult  = transaction.exec_prepared("find_subject", subjectId);
    pqxx::result prerequisiteResult = transaction.exec_prepared("find_subject_prerequisites", subjectId);
    pqxx::result corequisiteResult  = transaction.exec_prepared("find_subject_corequisites", subjectId);

    if (subjectResult.size() == 0) {
        throw DomainException("Subject not found");
    }

    set<string> prerequisites;
    for (auto row: prerequisiteResult) {
        prerequisites.insert(row[0].c_str());
    }

    set<string> corequisites;
    for (auto row: corequisiteResult) {
        corequisites.insert(row[0].c_str());
    }

    Subject subject(
        subjectId,
        string(subjectResult[0][0].c_str()),
        string(subjectResult[0][1].c_str()),
        stoi(subjectResult[0][2].c_str()),
        prerequisites,
        corequisites
    );

    return subject;
}

void SqlSubjectRepository::save(Subject& subject)
{
    this->_connection.prepare(
        "save_subject",
        "INSERT INTO subject (id, code, name, credits) \
        VALUES ($1, $2, $3, $4) \
        ON CONFLICT ON CONSTRAINT subject_pk DO \
        UPDATE SET \
        code = $2, \
        name = $3, \
        credits = $4 \
        WHERE subject.id = $1;"
    );

    this->_connection.prepare(
        "upsert_subject_prerequisites",
        "INSERT INTO subject_prerequisite (subject_id, prerequisite_id) \
        VALUES ($1, $2) \
        ON CONFLICT DO NOTHING;"
    );

    this->_connection.prepare(
        "upsert_subject_corequisites",
        "INSERT INTO subject_corequisite (subject_id, corequisite_id) \
        VALUES ($1, $2) \
        ON CONFLICT DO NOTHING;"
    );

    pqxx::work transaction{this->_connection};

    try {
        transaction.exec_prepared(
            "save_subject",
            subject.getId(),
            subject.getCode(),
            subject.getName(),
            subject.getCredits()
        );

        string prerequisitesIds;
        for (auto requisiteId: subject.getPrerequisites()) {
            if (prerequisitesIds.empty()) {
                prerequisitesIds = "'" + transaction.esc(requisiteId) + "'";
            } else {
                prerequisitesIds += ", '" + transaction.esc(requisiteId) + "'";
            }

            transaction.exec_prepared(
                "upsert_subject_prerequisites",
                subject.getId(),
                requisiteId
            );
        }

        string corequisitesIds;
        for (auto requisiteId: subject.getCorequisites()) {
            if (corequisitesIds.empty()) {
                corequisitesIds = "'" + transaction.esc(requisiteId) + "'";
            } else {
                corequisitesIds += ", '" + transaction.esc(requisiteId) + "'";
            }

            transaction.exec_prepared(
                "upsert_subject_corequisites",
                subject.getId(),
                requisiteId
            );
        }

        if (!prerequisitesIds.empty()) {
            transaction.exec(
                "DELETE FROM subject_prerequisite sp "
                "WHERE sp.subject_id = '" + transaction.esc(subject.getId()) + "' "
                "AND sp.prerequisite_id NOT IN (" + prerequisitesIds + ");"
            );
        } else {
            transaction.exec(
                "DELETE FROM subject_prerequisite sp "
                "WHERE sp.subject_id = '" + transaction.esc(subject.getId()) + "';"
            );
        }

        if (!corequisitesIds.empty()) {
            transaction.exec(
                "DELETE FROM subject_corequisite "
                "WHERE subject_id = '" + transaction.esc(subject.getId()) + "' "
                "AND corequisite_id NOT IN (" + corequisitesIds + ");"
            );
        } else {
            transaction.exec(
                "DELETE FROM subject_corequisite "
                "WHERE subject_id = '" + transaction.esc(subject.getId()) + "';"
            );
        }
    } catch(pqxx::failure const &e) {
        transaction.abort();

        throw e;
    }

    transaction.commit();
}

void SqlSubjectRepository::remove(string subjectId)
{
    pqxx::work transaction{this->_connection};

    try {
        this->_connection.prepare(
            "remove_subject_prerequisite",
            "DELETE FROM subject_prerequisite \
            WHERE subject_id = $1;"
        );

        this->_connection.prepare(
            "remove_subject_corequisite",
            "DELETE FROM subject_corequisite \
            WHERE subject_id = $1;"
        );

        this->_connection.prepare(
            "remove_subject",
            "DELETE FROM subject \
            WHERE id = $1;"
        );

        transaction.exec_prepared("remove_subject_prerequisite", subjectId);
        transaction.exec_prepared("remove_subject_corequisite", subjectId);
        transaction.exec_prepared("remove_subject", subjectId);

    } catch(pqxx::failure const &e) {
        transaction.abort();

        throw e;
    }

    transaction.commit();
}
