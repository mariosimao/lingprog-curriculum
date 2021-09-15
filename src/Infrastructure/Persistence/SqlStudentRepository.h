#ifndef SQL_STUDENT_REPOSITORY_H
#define SQL_STUDENT_REPOSITORY_H
#include <pqxx/pqxx>
#include "./../../Domain/Student.h"
#include "./../../Domain/IStudentRepository.h"

using namespace std;

class SqlStudentRepository: public IStudentRepository
{
    private:
        pqxx::connection* _connection;
    public:
        SqlStudentRepository(
            pqxx::connection* connection
        );
        Student findById(string studentId);
        void save(Student student);
        void remove(string studentId);
};
#endif
