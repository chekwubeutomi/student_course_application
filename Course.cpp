#include "Course.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <stdexcept>
using namespace std;

Course::Course(const string& name, const string& teacher){
    setName(name);
    setTeacher(teacher);
}

// ----- Getter ------
string Course::getName() const {return name;}
string Course::getTeacher() const { return teacher; }
size_t Course::getStudentCount() const { return students.size(); }

void Course::setName(const string& newName){
    if(newName.empty()) throw invalid_argument("Course name cannot be empty");
    name = newName;
}

void Course::setTeacher(const string& newTeacher) {
    if (newTeacher.empty()) throw invalid_argument("Teacher name cannot be empty");
    teacher = newTeacher;
}

// ----- Add a student --------
void Course::addStudent(unique_ptr<Student> student) {
    if (!student) {
        throw invalid_argument("Cannot add a null student");
    }
    students.push_back(move(student));
}

// ---------- Show all ----------
void Course::showAll() const {
    if (students.empty()) {
        cout << "No students in " << name << ".\n";
        return;
    }
    cout << "\n--- " << name << " (taught by " << teacher << ") ---\n";
    for (const auto& s : students) {
        cout << s->describe() << "\n";
    }
}

void Course::sortByGrade() {
    sort(students.begin(), students.end(),
         [](const unique_ptr<Student>& a, const unique_ptr<Student>& b) {
            return *a < *b;
         });
}

// ---------- Average ----------
void Course::showAverage() const {
    if (students.empty()) {
        cout << "No students to average.\n";
        return;
    }
    double sum = 0;
    for (const auto& s : students) {
        sum += s->getGrade();
    }
    cout << "Average for " << name << ": "
         << sum / students.size() << "\n";
}

// ---------- Grade distribution ----------
void Course::showGradeDistribution() const {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }
    map<char, int> counts;
    for (const auto& s : students) {
        counts[s->getLetterGrade()]++;
    }
    cout << "\nGrade distribution for " << name << ":\n";
    for (const auto& pair : counts) {
        cout << pair.first << ": " << pair.second << " student(s)\n";
    }
}

Student* Course::findStudent(const string& name) {
    auto it = find_if(students.begin(), students.end(),
        [&name](const unique_ptr<Student>& s) {
            return s->getName() == name;
        });

    if (it == students.end()) {
        return nullptr;   // not found
    }
    return it->get();     // return raw pointer (borrowed, not owned)
}

#include <fstream>

string Course::fileName() const {
    // Turn "CS101" into "CS101.txt"
    return name + ".txt";
}

void Course::saveToFile() const {
    ofstream out(fileName());
    if (!out.is_open()) {
        cout << "Could not save " << name << "\n";
        return;
    }

    // First line: course header
    out << "COURSE:" << name << "|" << teacher << "\n";

    // Then one line per student
    for (const auto& s : students) {
        const GraduateStudent* g =
            dynamic_cast<const GraduateStudent*>(s.get());

        if (g) {
            out << "G|" << g->getName() << "|" << g->getGrade()
                << "|" << g->getThesisTopic() << "\n";
        } else {
            out << "S|" << s->getName() << "|" << s->getGrade() << "\n";
        }
    }

    cout << "Saved " << name << " to " << fileName() << "\n";
}

void Course::loadFromFile() {
    ifstream in(fileName());
    if (!in.is_open()) {
        cout << "No saved file for " << name << "\n";
        return;
    }

    students.clear();
    string line;
    int loaded = 0;

    while (getline(in, line)) {
        if (line.empty()) continue;

        try {
            if (line.rfind("COURSE:", 0) == 0) {
                // Header line — we already have the name/teacher
                continue;
            }
            if (line[0] == 'G') {
                // G|name|grade|thesis
                size_t p1 = line.find('|');
                size_t p2 = line.find('|', p1 + 1);
                size_t p3 = line.find('|', p2 + 1);

                string sName = line.substr(p1 + 1, p2 - p1 - 1);
                double grade = stod(line.substr(p2 + 1, p3 - p2 - 1));
                string thesis = line.substr(p3 + 1);

                students.push_back(
                    make_unique<GraduateStudent>(sName, grade, thesis));
            } else if (line[0] == 'S') {
                // S|name|grade
                size_t p1 = line.find('|');
                size_t p2 = line.find('|', p1 + 1);

                string sName = line.substr(p1 + 1, p2 - p1 - 1);
                double grade = stod(line.substr(p2 + 1));

                students.push_back(
                    make_unique<Student>(sName, grade));
            }
            loaded++;
        }
        catch (const exception&) {
            cout << "Skipping bad line: " << line << "\n";
        }
    }

    cout << "Loaded " << loaded << " student(s) into " << name << "\n";
}
