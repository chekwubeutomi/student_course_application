#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED


#include <vector>
#include <memory>
#include <string>
#include "Course.h"

using namespace std;

class App {
private:
    vector<unique_ptr<Course>> courses;

public:
    // The main entry point
    void run();

private:
    // Menu actions
    void createCourse();
    void selectCourse();
    void deleteCourse();
    void listCourses() const;
    void saveAll() const;
    void loadAll();

    // Helper
    Course* chooseCourse();
};


#endif // APP_H_INCLUDED
