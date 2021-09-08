#ifndef CURRICULUM_H
#define CURRICULUM_H
#include <string>
#include "ProposedSemester.h"

using namespace std;

class Curriculum
{
    private:
        string _id;
        string _name;
        vector<ProposedSemester*> _semesters;
    public:
        Curriculum(
            string id,
            string name,
            vector<ProposedSemester*> semesters
        );
        void proposeSemester(
            int number,
            int freeCredits,
            int conditionedCredits,
            int restrictedCredits,
            vector<Subject*> subjects
        );
        void removeSemester(int semesterNumber);
};
#endif
