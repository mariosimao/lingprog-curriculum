#ifndef SQL_STUDENT_REPOSITORY_H
#define SQL_STUDENT_REPOSITORY_H
#include <pqxx/pqxx>
#include "./../../Domain/Student.h"

using namespace std;

class SqlStudentRepository
{
    private:
        pqxx::connection* _connection;
    public:
        void save(Student student);
};
#endif
