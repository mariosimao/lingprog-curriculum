#ifndef ADD_PRE_REQUISITE_HANDLER_H
#define ADD_PRE_REQUISITE_HANDLER_H
#include <string>
#include "../Domain/ISubjectRepository.h"

using namespace std;

class AddPrerequisiteHandler
{
    private:
        ISubjectRepository* _subjectRepository;
    public:
        AddPrerequisiteHandler(ISubjectRepository* subjectRepository);
        void execute(string subjectId, string prerequisiteId);
};
#endif
