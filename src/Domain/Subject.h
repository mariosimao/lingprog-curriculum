#ifndef SUBJECT_H
#define SUBJECT_H
#include <string>
#include <set>

using namespace std;

class Subject
{
    private:
        string _code;
        string _name;
        int _credits;
        set<string> _prerequisites;
        set<string> _corequisites;
    public:
        Subject(
            const string code,
            const string name,
            const int credits,
            const set<string> prerequisites,
            const set<string> corequisites
        );
        void addPrerequisite(const string prerequisite);
        void removePrequisite(const string prerequisite);
        void addCorequisite(const string corequisite);
        void removeCorequisite(const string corequisite);
};
#endif