/*
    Written by Luis Mendez
    Date Written: Jul 13, 2024
    Purpose: 
        Exam 4 - Student MANAGER
        Create a program that will keep track of students and their courses

    ---------- FEATURES ----------
    * Create/Update/Remove Student
    * Create/Update/Remove Class
    * View all students (sorted by last name)
    * View all courses (sorted by ID)
    * Search student and view courses
    * Search class and view amount of students
    * Menu system

    ------- ERROR PREVENTION -------
    * Free Students and Course lists
    
    ------ OTHER REQUIREMENTS ------
    * User provides size
    * Use header file
    
    ----- MENU -----
    1. View all students - DONE
    2. Search student
    3. View all courses
    4. Search courses
    5. Add student
    6. Add course
    7. Quit
*/

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

// Displays menu and returns option selected
int displayMenu();

// Adds course to student schedule
void addToCourse(STUDENT* student, COURSE** courseList, int MAX_COURSES);

// Displays all students in list
void viewStudents(STUDENT** student);

// Adds student to list
void addStudent(STUDENT** students, int MAX_COURSES, int MAX_STUDENTS);

// Adds course to list
void addCourse(COURSE** courses, int MAX_COURSES);

// Displays all courses
void viewCourses(COURSE** courses);

// Searches student and prints information and possible actions
void searchStudent(STUDENT** students, COURSE** courseList, int MAX_COURSES);

void myPause();

int main(){
    STUDENT** studentList;
    COURSE** courseList;
    int MAX_STUDENTS;
    int MAX_COURSES;

    // printf("Please enter max amount of students: "); scanf("%i",&MAX_STUDENTS);
    // printf("Please enter max amount of courses: "); scanf("%i",&MAX_COURSES);
    MAX_STUDENTS = 10;
    MAX_COURSES = 10;

    // Allocating memory
    studentList = calloc(MAX_STUDENTS, sizeof(STUDENT*));
    courseList = calloc(MAX_STUDENTS, sizeof(COURSE*));

    int option;
    do{
        option = displayMenu();
        switch(option){
            case 1: viewStudents(studentList); break;
            case 2: searchStudent(studentList, courseList, MAX_COURSES); break;
            case 3: viewCourses(courseList); break;
            case 5: addStudent(studentList, MAX_COURSES, MAX_STUDENTS); break;
            case 6: addCourse(courseList, MAX_COURSES); break;
        }
    }
    while(option != 7);


    // Freeing memory
    int i = 0;
    while(i < MAX_COURSES && courseList[i] != NULL) free(courseList[i++]);

    i = 0;
    while(i < MAX_STUDENTS && studentList[i] != NULL) free(studentList[i++]);

    return 0;
}

int displayMenu(){
    printf("\n\n======== STUDENT MANAGER ========\n");
    printf("1. View all students\n");
    printf("2. Search student\n");
    printf("3. View all courses\n");
    printf("4. Search courses\n");
    printf("5. Add student\n");
    printf("6. Add course\n");
    printf("7. Quit\n");
    printf("Option: ");
    int option;

    while(scanf("%i", &option) != 1 || option > 7 || option < 1){
        printf("Option invalid, please try again: ");
        getchar();
    }

    return option;
}

void addToCourse(STUDENT* student, COURSE** courseList, int MAX_COURSES){
    // Finding course
    int courseID;
    int amountOfClasses = 0;
    
    printf("\nAvailable classes:\n");
    for(int i=0; courseList[i]!=NULL; i++){
        if(courseList[i]->active){
            amountOfClasses++;
            printf("%i. %s\n", i, courseList[i]->name);
        }
    }
    if(amountOfClasses == 0){
        printf("There are no available classes.\n");
        return;
    }

    printf("Select class to add: "); 
    while(scanf(" %i", &courseID)!=1 || courseID < 0 || courseID >= amountOfClasses){
        printf("Wrong option. Please try again: "); getchar();
    }

    COURSE* course = courseList[courseID];

    // Adding to student schedule
    int position = 0;
    while(position < MAX_COURSES && student->courses[position] != NULL) position++;

    if(position < MAX_COURSES) {
        student->courses[position] = course;
        student->courses[position]->registeredStudents++;
        printf("CLASS \"%s\" ADDED TO %s's SCHEDULE", course->name, student->last_name);
    }else{
        printf("Sorry, you have reached the maximum amount of classes.");
    }
}

void viewStudents(STUDENT** students){
    printf("\n======= ALL STUDENTS =======\n");
    if(students[0] == NULL) {printf("There are not students to show."); PAUSE; return;}

    printf("ID\tFIRST\tLAST\n");
    int current = 0;
    for(int i=0; students[i] != NULL; i++){
        if(students[i]->active)printf("%i\t%s\t%s\n", students[i]->id, students[i]->first_name, students[i]->last_name);
    }

    PAUSE;
}

void addStudent(STUDENT** students, int MAX_COURSES, int MAX_STUDENTS){
    STUDENT* newStudent = calloc(1, sizeof(STUDENT));
    newStudent->courses = calloc(MAX_COURSES, sizeof(COURSE*));

    printf("\n====== ADDING STUDENT ======\n");
    printf("Enter first name: "); scanf(" %[^\n]", newStudent->first_name);
    printf("Enter last name: "); scanf(" %[^\n]", newStudent->last_name);

    int position = 0;
    while(students[position] != NULL){
        position++;
    } 

    newStudent->id = position;
    newStudent->active = 1;

    if(position < MAX_STUDENTS) {
        students[position] = newStudent;
        printf("STUDENT \"%s\" ADDED", newStudent->last_name);
    }else{
        printf("Sorry, you have reached the maximum amount of students.");
    }

    PAUSE;

}

void addCourse(COURSE** courses, int MAX_COURSES){
    COURSE* newCourse = calloc(1, sizeof(COURSE));

    printf("\n====== ADDING COURSE ======\n");
    printf("Enter course name: "); scanf(" %[^\n]", newCourse->name);

    int position = 0;
    while(courses[position] != NULL){position++;} 

    newCourse->id = position;
    newCourse->registeredStudents = 0;
    newCourse->active = 1;

    if(position < MAX_COURSES) {
        courses[position] = newCourse;
        printf("COURSE \"%s\" ADDED", newCourse->name);
    }else{
        printf("Sorry, you have reached the maximum amount of courses.");
    }

    PAUSE;

}

void viewCourses(COURSE** courses){
    printf("\n======= ALL COURSES =======\n");
    if(courses[0] == NULL) {printf("There are not courses to show."); PAUSE; return;}

    printf("ID\tNAME\tREGISTERED\n");
    int current = 0;
    for(int i=0; courses[i] != NULL; i++){
        if(courses[i]->active)printf("%i\t%s\t%i\n", courses[i]->id, courses[i]->name, courses[i]->registeredStudents);
    }

    PAUSE;
}

void searchStudent(STUDENT** students, COURSE** courseList, int MAX_COURSES){
    int id;
    printf("\n====== SEARCHING STUDENT ======\n");
    int found = 0;
    char option;
    STUDENT* student;
    do{
        printf("Enter student ID: "); scanf("%i", &id);

        for(int i=0; students[i]!=NULL; i++){
            if(students[i]->id == id && students[i]->active){
                // Found, print info
                student = students[i];
                found = 1;

                printf("\nSTUDENT FOUND\n");
                printf("%s, %s (#%i)\n", students[i]->last_name, students[i]->first_name, students[i]->id);
                printf("COURSES:\n");
                int hasRegistered = 0;
                
                for(int j=0; students[i]->courses[j]!=NULL; j++){
                    printf("- %s\n", students[i]->courses[j]->name);
                    hasRegistered = 1;
                }
                if(!hasRegistered) printf("Not registered in any course.\n");

                break;

                
            }
        }
        if(!found){
            // Not found
            printf("Student not found. Would you like to try again? (Y/N): ");
            while(scanf(" %c", &option)!=1 || (option != 'Y' && option != 'y' && option != 'N' && option != 'n')){
                printf("Invalid option. Please try again: "); getchar();
            }
        }
    }while(!found && (option=='y' || option=='Y'));
    
    if(found){
        int action;
        printf("\nWhat would you like to do?\n");
        printf("1. Add to course\n");
        printf("2. Update student\n");
        printf("3. Remove student\n");
        printf("4. Go back\n");
        printf("Option: ");
        while(scanf(" %i", &action) != 1 || action < 1 || action > 4){
            printf("Invalid option. Please try again: "); getchar();
        }

        switch(action){
            case 1: addToCourse(student, courseList, MAX_COURSES); break;
        }
    }

    PAUSE;
}

void myPause() {
	printf("\n\nPress ENTER to continue....\n");
	getchar(); getchar();
}