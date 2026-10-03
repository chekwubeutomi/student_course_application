# Student Grade Manager

A simple C++ application for managing multiple courses and tracking student grades. The program supports adding regular students and graduate students, sorting by performance, calculating averages, visualizing grade distribution, and saving/loading course data to text files.

## Features

- Create and manage multiple courses
- List and delete courses
- Add a standard student with a grade
- Add a graduate student with a thesis topic
- Display all students in a course
- Sort students by grade
- Show course average
- Show grade distribution by letter grade
- Save a course to a text file
- Load a previously saved course

## Project Overview

The application follows a simple object-oriented design:

- `Student` stores the student name and numeric grade and calculates the letter grade
- `GraduateStudent` extends `Student` with a thesis topic
- `Course` manages a collection of students and handles file persistence
- `App` provides the menu-driven command interface

## Application Menu

When the program starts, it presents a menu like this:

1. Create course
2. List courses
3. Select course
4. Delete course
5. Save all
6. Load all
7. Quit

After selecting a course, you can:

1. Add student
2. Add graduate student
3. Show all
4. Sort by grade
5. Show average
6. Show distribution
7. Save this course
8. Load this course
9. Back

## Data Storage

Each course is saved to a file using the course name as the filename.

Example:

- `Math.txt`
- `CS101.txt`

The file format is:

```text
COURSE:Math|John
S|Mike|67
G|Ken|80|Machine Learning
```

- `S` = standard student
- `G` = graduate student
- The course header stores the course name and teacher

## Example Student Grade Rules

The system converts numeric grades to letter grades using:

- 90–100: A
- 80–89: B
- 70–79: C
- 60–69: D
- Below 60: F

Grades are validated to remain in the range 0 to 100.

## File Structure

```text
studentgrader/
├── App.cpp
├── App.h
├── Course.cpp
├── Course.h
├── GraduateStudent.cpp
├── GraduateStudent.h
├── Student.cpp
├── Student.h
├── main.cpp
├── Math.txt
├── students.txt
├── studentgrader.cbp
├── studentgrader.depend
├── studentgrader.layout
└── README.md
```

## Running the Application

### Option 1: Code::Blocks

1. Open `studentgrader.cbp` in Code::Blocks.
2. Build the project.
3. Run the application from the IDE.

### Option 2: Command Line (GCC/MinGW)

If you have a C++ compiler installed, run:

```bash
g++ -std=c++17 *.cpp -o studentgrader
./studentgrader
```

On Windows with MinGW, this is typically:

```bash
g++ -std=c++17 *.cpp -o studentgrader.exe
studentgrader.exe
```

## Notes

- This is a small academic-style project intended for learning C++ object-oriented design.
- Course and student data are stored as plain text files in the project folder.
- Some sample files are included in the repository for demonstration.

## License

This project is provided for educational use.
