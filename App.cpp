#include "App.h"
#include <iostream>
#include <limits>
using namespace std;

void App::run() {
    while (true) {
        cout << "\n===== Student Grade Manager =====\n";
        cout << "1. Create course\n";
        cout << "2. List courses\n";
        cout << "3. Select course\n";
        cout << "4. Delete course\n";
        cout << "5. Save all\n";
        cout << "6. Load all\n";
        cout << "7. Quit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: createCourse(); break;
            case 2: listCourses();  break;
            case 3: selectCourse(); break;
            case 4: deleteCourse(); break;
            case 5: saveAll();      break;
            case 6: loadAll();      break;
            case 7: cout << "Goodbye!\n"; return;
            default: cout << "Invalid choice.\n";
        }
    }
}

void App::createCourse() {
    string name, teacher;
    cout << "Course name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Teacher: ";
    getline(cin, teacher);

    try {
        courses.push_back(make_unique<Course>(name, teacher));
        cout << "Course created.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void App::listCourses() const {
    if (courses.empty()) {
        cout << "No courses.\n";
        return;
    }
    for (size_t i = 0; i < courses.size(); i++) {
        cout << i + 1 << ". " << courses[i]->getName()
             << " (" << courses[i]->getStudentCount() << " students)\n";
    }
}

Course* App::chooseCourse() {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return nullptr;
    }
    listCourses();
    cout << "Select course number: ";
    int idx;
    cin >> idx;
    if (cin.fail() || idx < 1 || idx > (int)courses.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid selection.\n";
        return nullptr;
    }
    return courses[idx - 1].get();
}

void App::selectCourse() {
    Course* c = chooseCourse();
    if (!c) return;

    while (true) {
        cout << "\n--- " << c->getName() << " ---\n";
        cout << "1. Add student\n";
        cout << "2. Add graduate student\n";
        cout << "3. Show all\n";
        cout << "4. Sort by grade\n";
        cout << "5. Show average\n";
        cout << "6. Show distribution\n";
        cout << "7. Save this course\n";
        cout << "8. Load this course\n";
        cout << "9. Back\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid.\n";
            continue;
        }

        try {
            if (choice == 1) {
                string n; double g;
                cout << "Name: "; cin.ignore(); getline(cin, n);
                cout << "Grade: "; cin >> g;
                c->addStudent(make_unique<Student>(n, g));
            }
            else if (choice == 2) {
                string n, t; double g;
                cout << "Name: "; cin.ignore(); getline(cin, n);
                cout << "Grade: "; cin >> g;
                cout << "Thesis: "; cin.ignore(); getline(cin, t);
                c->addStudent(make_unique<GraduateStudent>(n, g, t));
            }
            else if (choice == 3) c->showAll();
            else if (choice == 4) { c->sortByGrade(); cout << "Sorted.\n"; }
            else if (choice == 5) c->showAverage();
            else if (choice == 6) c->showGradeDistribution();
            else if (choice == 7) c->saveToFile();
            else if (choice == 8) c->loadFromFile();
            else if (choice == 9) return;
            else cout << "Invalid choice.\n";
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

void App::deleteCourse() {
    Course* c = chooseCourse();
    if (!c) return;
    // Find the matching index
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].get() == c) {
            cout << "Deleted " << c->getName() << "\n";
            courses.erase(courses.begin() + i);
            return;
        }
    }
}

void App::saveAll() const {
    for (const auto& c : courses) {
        c->saveToFile();
    }
}

void App::loadAll() {
    // In a real app you'd scan a directory.
    // For now, ask the user which course to load by name.
    string name;
    cout << "Course name to load: ";
    cin.ignore();
    getline(cin, name);

    // Do we already have it?
    for (const auto& c : courses) {
        if (c->getName() == name) {
            c->loadFromFile();
            return;
        }
    }

    // Otherwise create a new course shell and load into it
    try {
        auto newCourse = make_unique<Course>(name, "Unknown");
        newCourse->loadFromFile();
        courses.push_back(move(newCourse));
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}
