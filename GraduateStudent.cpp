#include "GraduateStudent.h"
#include <stdexcept>
using namespace std;

GraduateStudent::GraduateStudent(const string& name, double grade,
                                 const string& thesisTopic)
    : Student(name, grade), thesisTopic(thesisTopic) {
}

string GraduateStudent::getThesisTopic() const { return thesisTopic; }

void GraduateStudent::setThesisTopic(const string& t) {
    if (t.empty()) throw invalid_argument("Thesis topic cannot be empty");
    thesisTopic = t;
}

string GraduateStudent::describe() const {
    return Student::describe() + " [Graduate: " + thesisTopic + "]";
}
