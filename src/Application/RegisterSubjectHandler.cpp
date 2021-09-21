#include <set>
#include <string>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RegisterSubjectHandler.h"
#include "../Domain/Subject.h"
#include "../Domain/ISubjectRepository.h"

RegisterSubjectHandler::RegisterSubjectHandler(ISubjectRepository* subjectRepository)
{
    this->_subjectRepository = subjectRepository;
}

string RegisterSubjectHandler::execute(
    string code,
    string name,
    int credits,
    set<string> prerequisites,
    set<string> corequisites
) {
    string id = boost::uuids::to_string(boost::uuids::random_generator()());

    Subject* subject = new Subject(id, code, name, credits, prerequisites, corequisites);

    this->_subjectRepository->save(subject);

    return id;
}
