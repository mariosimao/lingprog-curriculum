#ifndef REGISTER_SUBJECT_HANDLER_H
#define REGISTER_SUBJECT_HANDLER_H
#include <set>
#include <string>
#include "../Domain/ISubjectRepository.h"

using namespace std;

class RegisterSubject
{
    private:
        ISubjectRepository& _subjectRepository;
    public:
        RegisterSubject(ISubjectRepository& subjectRepository);
        string execute(
            string code,
            string name,
            int credits,
            set<string> prerequisites,
            set<string> corequisites
        );
};
#endif
