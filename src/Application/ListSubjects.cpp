#include "ListSubjects.h"
#include "../Domain/Student.h"

ListSubjects::ListSubjects(ISubjectRepository& subjectRepository):
    _subjectRepository(subjectRepository) {}

vector<SubjectView> ListSubjects::execute()
{
    vector<Subject> subjects = this->_subjectRepository.findAll();

    vector<SubjectView> result;
    for (auto subject: subjects) {
        SubjectView view {
            subject.getId(),
            subject.getCode(),
            subject.getName(),
            subject.getCredits()
        };

        result.push_back(view);
    }

    return result;
}
