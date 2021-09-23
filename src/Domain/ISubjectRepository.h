#ifndef I_SUBJECT_REPOSITORY_H
#define I_SUBJECT_REPOSITORY_H
#include "Subject.h"

class ISubjectRepository
{
    public:
        ~ISubjectRepository() { };
        virtual Subject findById(string subjectId) = 0;
        virtual bool subjectCodeExists(string code) = 0;
        virtual void save(Subject& subject) = 0;
        virtual void remove(string subjectId) = 0;
};
#endif
