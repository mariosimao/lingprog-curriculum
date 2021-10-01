#ifndef REMOVE_SUBJECT_H
#define REMOVE_SUBJECT_H
#include <string>
#include "../Domain/ISubjectRepository.h"

using namespace std;

class RemoveSubject
{
    private:
        ISubjectRepository& _subjectRepository;
    public:
        RemoveSubject(ISubjectRepository& subjectRepository);
        void execute(string subjectId);
};
#endif
