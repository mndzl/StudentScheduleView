#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PAUSE myPause()

typedef struct {
    int id;
    char name[50];
    int registeredStudents;
    int active; // true or false
} COURSE;

typedef struct {
    int id;
    char first_name[50];
    char last_name[50];
    COURSE** courses;
    int active; // true or false
} STUDENT;

// Displays menu and returns option by user
int displayMenu();

// Adds course to student schedule
void addToCourse(STUDENT* student, COURSE** courseList, int MAX_COURSES);

// Displays all students in list
void viewStudents(STUDENT** student);

// Adds student to list
void addStudent(STUDENT** students, int MAX_COURSES, int MAX_STUDENTS);

void addCourse(COURSE** courses, int MAX_COURSES);

// Displays all courses
void viewCourses(COURSE** courses);

// Searches student and prints information and possible actions
void searchStudent(STUDENT** students, COURSE** courseList, int MAX_COURSES);

// Lets you update an student
void updateStudent(STUDENT* student);

// Lets you set a student as inactive
void removeStudent(STUDENT* student);

// Helper method, returns true or false if the students is in the course
int isRegistered(STUDENT* student, COURSE* course);

void myPause();