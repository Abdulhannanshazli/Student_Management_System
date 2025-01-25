#include "Student.h"
#include <filesystem>

Student::Student(int id, const std::string& fname, const std::string& lname)
    : studentID(id), firstName(fname), lastName(lname), totalMarks(0), percentage(0), grade('F') {}

void Student::addMarks(double mark) {
    if (mark >= 0 && mark <= 100) {
        marks.push_back(mark);
        calculateTotalMarks();
        calculatePercentage();
        calculateGrade();
    } else {
        throw std::invalid_argument("Mark must be between 0 and 100");
    }
}

void Student::calculateGrade() {
    if (percentage >= 85) grade = 'A';
    else if (percentage >= 70) grade = 'B';
    else if (percentage >= 50) grade = 'C';
    else grade = 'F';
}

void Student::displayStudentDetails() const {
    std::cout << "\nStudent Details:" << std::endl;
    std::cout << "ID: " << studentID << std::endl;
    std::cout << "Name: " << firstName << " " << lastName << std::endl;
    std::cout << "DOB: " << dob << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phoneNumber << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Percentage: " << std::fixed << std::setprecision(2) << percentage << "%" << std::endl;
}

void Student::displayMarks() const {
    std::cout << "\nMarks:" << std::endl;
    for (size_t i = 0; i < marks.size(); ++i) {
        std::cout << "Subject " << (i + 1) << ": " << marks[i] << std::endl;
    }
    std::cout << "Total Marks: " << totalMarks << std::endl;
}

void Student::calculateTotalMarks() {
    totalMarks = 0;
    for (double mark : marks) {
        totalMarks += mark;
    }
}

void Student::calculatePercentage() {
    if (!marks.empty()) {
        percentage = (totalMarks / (marks.size() * 100)) * 100;
    } else {
        percentage = 0;
    }
}

bool Student::saveStudentToFile() const {
    // Create students directory if it doesn't exist
    std::filesystem::create_directories("students");
    
    std::ofstream file("students/" + std::to_string(studentID) + ".txt");
    if (!file) return false;

    file << studentID << "\n" << firstName << "\n" << lastName << "\n"
         << dob << "\n" << gender << "\n" << email << "\n"
         << phoneNumber << "\n" << address << "\n";

    for (double mark : marks) {
        file << mark << " ";
    }
    file << "\n";
    
    return true;
}

bool Student::loadStudentFromFile(int id) {
    std::ifstream file("students/" + std::to_string(id) + ".txt");
    if (!file) return false;

    marks.clear();
    
    file >> studentID;
    file.ignore();
    std::getline(file, firstName);
    std::getline(file, lastName);
    std::getline(file, dob);
    std::getline(file, gender);
    std::getline(file, email);
    std::getline(file, phoneNumber);
    std::getline(file, address);

    double mark;
    while (file >> mark) {
        marks.push_back(mark);
    }

    calculateTotalMarks();
    calculatePercentage();
    calculateGrade();

    return true;
} 