#include "RemoveSubject.h"
#include "../Domain/Student.h"
#include "../Domain/StudentSemester.h"
#include "../Domain/Subject.h"

RemoveSubject::RemoveSubject(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

void RemoveSubject::execute(string subjectId)
{
    this->_subjectRepository.remove(subjectId);

    return;
}
