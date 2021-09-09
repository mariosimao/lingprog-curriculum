#ifndef SQL_SUBJECT_REPOSITORY_H
#define SQL_SUBJECT_REPOSITORY_H
#include <pqxx/pqxx>
#include "./../../Domain/Subject.h"
#include "./../../Domain/ISubjectRepository.h"

using namespace std;

class SqlSubjectRepository: public ISubjectRepository
{
    private:
        pqxx::connection* _connection;
    public:
        SqlSubjectRepository(
            pqxx::connection* connection
        );
        Subject findById(const string subjectId);
        void save(const Subject subject);
        void remove(const string subjectId);
};
#endif
