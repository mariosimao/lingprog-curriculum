#ifndef LIST_SUBJECTS_H
#define LIST_SUBJECTS_H
#include <vector>
#include "Views/SubjectView.h"
#include "../Domain/ISubjectRepository.h"

using namespace std;

class ListSubjects
{
    private:
        ISubjectRepository& _subjectRepository;
    public:
        ListSubjects(ISubjectRepository& subjectRepository);
        vector<SubjectView> execute();
};
#endif
