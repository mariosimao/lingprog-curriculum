#ifndef PROPOSED_SEMESTER_H
#define PROPOSED_SEMESTER_H
#include <string>
#include <vector>
#include "Subject.h"

using namespace std;

class ProposedSemester
{
    private:
        int _number;
        int _freeCredits;
        int _conditionedCredits;
        int _restrictedCredits;
        vector<Subject*> _subjects;
    public:
        ProposedSemester(
            int number,
            int freeCredits,
            int conditionedCredits,
            int restrictedCredits,
            vector<Subject*> subjects
        );
};
#endif
