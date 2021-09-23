#include <set>
#include <string>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RegisterSubject.h"
#include "../Domain/Subject.h"
#include "../Domain/ISubjectRepository.h"
#include "../Domain/DomainException.h"

RegisterSubject::RegisterSubject(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

string RegisterSubject::execute(
    string code,
    string name,
    int credits,
    set<string> prerequisites,
    set<string> corequisites
) {
    if (this->_subjectRepository.subjectCodeExists(code)) {
        throw DomainException("Subject with this code already exist.");
    }

    string id = boost::uuids::to_string(boost::uuids::random_generator()());

    Subject subject(id, code, name, credits, prerequisites, corequisites);

    this->_subjectRepository.save(subject);

    return id;
}
