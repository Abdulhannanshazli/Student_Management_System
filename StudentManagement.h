#pragma once
#include "Student.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

class StudentManagement {
private:
    std::vector<Student> studentList;
    int nextID;

    int generateUniqueID() { return nextID++; }

public:
    StudentManagement() : nextID(1) {}

    bool addStudent(const Student& student);
    bool updateStudent(int studentID);
    bool deleteStudent(int studentID);
    void viewStudentDetails(int studentID) const;
    std::vector<Student> searchStudentByName(const std::string& name) const;
    Student* searchStudentByID(int studentID);
    void displayAllStudents() const;
    void generateReport() const;
    bool saveAllStudentsToFile() const;
    bool loadAllStudentsFromFile();
    void sortStudentsByName();
    void sortStudentsByGrade();
    Student* findTopStudent();
    double findAverageMarks() const;
    void calculateClassRanks();
}; 