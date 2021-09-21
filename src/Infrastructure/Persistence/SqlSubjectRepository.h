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
        pqxx::connection* _connection;
        map<string, Subject*> _mapByCode;
    public:
        SqlSubjectRepository(
            pqxx::connection* connection
        );
        Subject* findById(const string subjectId);
        void save(Subject* subject);
        void remove(const string subjectId);
};
#endif
