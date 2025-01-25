#include "StudentManagement.h"
#include <filesystem>
#include <algorithm>
#include <fstream>

bool StudentManagement::addStudent(const Student& student) {
    // Check if student with same ID already exists
    if (searchStudentByID(student.getStudentID()) != nullptr) {
        return false;
    }
    
    studentList.push_back(student);
    return true;
}

bool StudentManagement::updateStudent(int studentID) {
    Student* student = searchStudentByID(studentID);
    if (!student) return false;

    std::string input;
    std::cout << "\nUpdating student with ID: " << studentID << std::endl;
    
    std::cout << "Enter new first name (or press enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setFirstName(input);

    std::cout << "Enter new last name (or press enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setLastName(input);

    std::cout << "Enter new email (or press enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setEmail(input);

    std::cout << "Enter new phone number (or press enter to skip): ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setPhoneNumber(input);

    return true;
}

bool StudentManagement::deleteStudent(int studentID) {
    auto it = std::find_if(studentList.begin(), studentList.end(),
        [studentID](const Student& s) { return s.getStudentID() == studentID; });
    
    if (it != studentList.end()) {
        studentList.erase(it);
        return true;
    }
    return false;
}

void StudentManagement::viewStudentDetails(int studentID) const {
    auto it = std::find_if(studentList.begin(), studentList.end(),
        [studentID](const Student& s) { return s.getStudentID() == studentID; });
    
    if (it != studentList.end()) {
        it->displayStudentDetails();
        it->displayMarks();
    } else {
        std::cout << "Student not found." << std::endl;
    }
}

std::vector<Student> StudentManagement::searchStudentByName(const std::string& name) const {
    std::vector<Student> results;
    for (const auto& student : studentList) {
        if (student.getFirstName().find(name) != std::string::npos ||
            student.getLastName().find(name) != std::string::npos) {
            results.push_back(student);
        }
    }
    return results;
}

Student* StudentManagement::searchStudentByID(int studentID) {
    auto it = std::find_if(studentList.begin(), studentList.end(),
        [studentID](const Student& s) { return s.getStudentID() == studentID; });
    
    return it != studentList.end() ? &(*it) : nullptr;
}

void StudentManagement::displayAllStudents() const {
    if (studentList.empty()) {
        std::cout << "No students found." << std::endl;
        return;
    }

    std::cout << "\nAll Students:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    for (const auto& student : studentList) {
        student.displayStudentDetails();
        std::cout << std::string(50, '-') << std::endl;
    }
}

void StudentManagement::generateReport() const {
    if (studentList.empty()) {
        std::cout << "No students to generate report." << std::endl;
        return;
    }

    int totalStudents = studentList.size();
    double totalPercentage = 0;
    Student* topStudent = nullptr;
    double highestPercentage = 0;

    for (const auto& student : studentList) {
        totalPercentage += student.getPercentage();
        if (student.getPercentage() > highestPercentage) {
            highestPercentage = student.getPercentage();
            topStudent = const_cast<Student*>(&student);
        }
    }

    std::cout << "\nStudent Management System Report" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Total number of students: " << totalStudents << std::endl;
    std::cout << "Average percentage: " << std::fixed << std::setprecision(2) 
              << (totalPercentage / totalStudents) << "%" << std::endl;
    
    if (topStudent) {
        std::cout << "\nTop performing student:" << std::endl;
        topStudent->displayStudentDetails();
    }
}

bool StudentManagement::saveAllStudentsToFile() const {
    std::filesystem::create_directories("students");
    
    std::ofstream indexFile("students/index.txt");
    if (!indexFile) return false;

    for (const auto& student : studentList) {
        indexFile << student.getStudentID() << "\n";
        if (!student.saveStudentToFile()) return false;
    }

    return true;
}

bool StudentManagement::loadAllStudentsFromFile() {
    studentList.clear();
    std::ifstream indexFile("students/index.txt");
    if (!indexFile) return false;

    int studentID;
    while (indexFile >> studentID) {
        Student student;
        if (student.loadStudentFromFile(studentID)) {
            studentList.push_back(student);
            if (studentID >= nextID) nextID = studentID + 1;
        }
    }

    return true;
}

void StudentManagement::sortStudentsByName() {
    std::sort(studentList.begin(), studentList.end(),
        [](const Student& a, const Student& b) {
            return a.getLastName() + a.getFirstName() < b.getLastName() + b.getFirstName();
        });
}

void StudentManagement::sortStudentsByGrade() {
    std::sort(studentList.begin(), studentList.end(),
        [](const Student& a, const Student& b) {
            return a.getPercentage() > b.getPercentage();
        });
}

Student* StudentManagement::findTopStudent() {
    if (studentList.empty()) return nullptr;
    
    return &(*std::max_element(studentList.begin(), studentList.end(),
        [](const Student& a, const Student& b) {
            return a.getPercentage() < b.getPercentage();
        }));
}

double StudentManagement::findAverageMarks() const {
    if (studentList.empty()) return 0.0;

    double totalPercentage = 0;
    for (const auto& student : studentList) {
        totalPercentage += student.getPercentage();
    }
    return totalPercentage / studentList.size();
}

void StudentManagement::calculateClassRanks() {
    // Sort by percentage in descending order
    sortStudentsByGrade();
    
    std::cout << "\nClass Rankings:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (size_t i = 0; i < studentList.size(); ++i) {
        std::cout << "Rank " << (i + 1) << ": "
                 << studentList[i].getFirstName() << " " 
                 << studentList[i].getLastName()
                 << " (Percentage: " << std::fixed << std::setprecision(2) 
                 << studentList[i].getPercentage() << "%)" << std::endl;
    }
} 