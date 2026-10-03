#include "Student.h"
#include <stdexcept>
#include <iostream>

Student::Student(const string& name, double grade){
    setName(name);
    setGrade(grade);
}


string Student::getName() const { return name; }
double Student::getGrade() const { return grade; }

void Student::setName(const string& newName) {
    if (newName.empty()) throw invalid_argument("Name cannot be empty");
    name = newName;
}

void Student::setGrade(double newGrade) {
    if (newGrade < 0 || newGrade > 100)
        throw invalid_argument("Grade must be between 0 and 100");
    grade = newGrade;
}

char Student::getLetterGrade() const {
    if (grade >= 90) return 'A';
    if (grade >= 80) return 'B';
    if (grade >= 70) return 'C';
    if (grade >= 60) return 'D';
    return 'F';
}

string Student::describe() const {
    return name + " - " + to_string(grade) + " (" + getLetterGrade() + ")";
}

bool Student::operator<(const Student& other) const {
    return grade > other.grade;
}

ostream& operator<<(ostream& os, const Student& s) {
    os << s.getName() << " - " << s.getGrade()
       << " (" << s.getLetterGrade() << ")";
    return os;
}
