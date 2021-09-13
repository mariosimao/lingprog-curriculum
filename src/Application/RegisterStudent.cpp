#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RegisterStudent.h"
#include "../Domain/Student.h"

RegisterStudent::RegisterStudent(IStudentRepository* studentRepository)
{
    this->_studentRepository = studentRepository;
}

string RegisterStudent::execute(string name, string curriculumId)
{
    string id = boost::uuids::to_string(boost::uuids::random_generator()());

    Student student(id, name, curriculumId);

    this->_studentRepository->save(student);

    return id;
}
