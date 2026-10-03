#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <string>
using namespace std;

class Student {
protected:
    string name;
    double grade;

public:
    Student(const string& name, double grade);

    string getName() const;
    double getGrade() const;
    char getLetterGrade() const;

    void setName(const string& newName);
    void setGrade(double newGrade);

    virtual string describe() const;
    virtual ~Student(){}

    bool operator<(const Student& other) const;
};

ostream& operator<<(ostream& os, const Student& s);


#endif // STUDENT_H_INCLUDED
