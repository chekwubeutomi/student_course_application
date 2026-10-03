#ifndef GRADUATESTUDENT_H_INCLUDED
#define GRADUATESTUDENT_H_INCLUDED

#include "Student.h"

class GraduateStudent : public Student {
private:
    string thesisTopic;

public:
    GraduateStudent(const string& name, double grade, const string& thesisTopic);
    string getThesisTopic() const;
    void setThesisTopic(const string& t);
    string describe() const override;
};

#endif // GRADUATESTUDENT_H_INCLUDED
