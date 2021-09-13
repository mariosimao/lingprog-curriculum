#ifndef SUBJECT_CLI_CONTROLLER_H
#define SUBJECT_CLI_CONTROLLER_H
#include <string>
#include <vector>
#include "../../Domain/ISubjectRepository.h"

using namespace std;

class SubjectCliController
{
    private:
        ISubjectRepository* _subjectRepository;
    public:
        SubjectCliController(ISubjectRepository* subjectRepository);
        void registerSubject(vector<string> arguments);
        void addPrerequisite(vector<string> arguments);
};
#endif
