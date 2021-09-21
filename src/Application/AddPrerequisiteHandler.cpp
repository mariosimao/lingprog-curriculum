#include <string>
#include "AddPrerequisiteHandler.h"
#include "../Domain/Subject.h"
#include "../Domain/ISubjectRepository.h"

AddPrerequisiteHandler::AddPrerequisiteHandler(ISubjectRepository* subjectRepository)
{
    this->_subjectRepository = subjectRepository;
}

void AddPrerequisiteHandler::execute(string subjectId, string prerequisiteId)
{
    Subject* subject = this->_subjectRepository->findById(subjectId);
    Subject* requisite = this->_subjectRepository->findById(prerequisiteId);

    subject->addPrerequisite(requisite->getId());

    this->_subjectRepository->save(subject);

    return;
}
