#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include "Student.h"
#include "GraduateStudent.h"
using namespace std;

class Course {
private:
    string name;
    string teacher;
    vector<unique_ptr<Student>> students;
    string fileName() const;

public:
    Course(const string& name, const string& teacher);

    string getName() const;
    string getTeacher() const;
    size_t getStudentCount() const;

    //setters
    void setName(const string& newName);
    void setTeacher(const string& newTeacher);

    // Core operations
    void addStudent(unique_ptr<Student> student);
    void showAll() const;
    void sortByGrade();
    void showAverage() const;
    void showGradeDistribution() const;
    Student* findStudent(const string& name);
    void saveToFile() const;
    void loadFromFile();


};





#endif // COURSE_H_INCLUDED
