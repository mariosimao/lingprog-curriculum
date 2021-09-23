#ifndef SUBJECT_H
#define SUBJECT_H
#include <string>
#include <set>

using namespace std;

class Subject
{
    private:
        string _id;
        string _code;
        string _name;
        int _credits;
        set<string> _prerequisites;
        set<string> _corequisites;
    public:
        Subject(
            string id,
            string code,
            string name,
            int credits,
            set<string> prerequisites,
            set<string> corequisites
        );
        string getId();
        string getCode();
        string getName();
        int getCredits();
        set<string> getPrerequisites();
        set<string> getCorequisites();
        void addPrerequisite(string prerequisite);
        void removePrequisite(string prerequisite);
        void addCorequisite(string corequisite);
        void removeCorequisite(string corequisite);
};
#endif