#ifndef SQL_SUBJECT_REPOSITORY_H
#define SQL_SUBJECT_REPOSITORY_H
#include <map>
#include <pqxx/pqxx>
#include "./../../Domain/Subject.h"
#include "./../../Domain/ISubjectRepository.h"

using namespace std;

class SqlSubjectRepository: public ISubjectRepository
{
    private:
        pqxx::connection& _connection;
    public:
        SqlSubjectRepository(pqxx::connection& connection);
        ~SqlSubjectRepository() {};
        Subject findById(string subjectId);
        void save(Subject& subject);
        void remove(string subjectId);
};
#endif
