#ifndef I_SUBJECT_REPOSITORY_H
#define I_SUBJECT_REPOSITORY_H
#include "Subject.h"

class ISubjectRepository
{
    public:
        virtual Subject* findById(const string subjectId) = 0;
        virtual void save(Subject* subject) = 0;
        virtual void remove(const string subjectId) = 0;
};
#endif
