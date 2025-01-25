#include "StudentManagement.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\nStudent Management System" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Update Student" << std::endl;
    std::cout << "3. Delete Student" << std::endl;
    std::cout << "4. View Student Details" << std::endl;
    std::cout << "5. Search Student by Name" << std::endl;
    std::cout << "6. Display All Students" << std::endl;
    std::cout << "7. Generate Report" << std::endl;
    std::cout << "8. Calculate Class Rankings" << std::endl;
    std::cout << "9. Save Data" << std::endl;
    std::cout << "10. Load Data" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

Student inputStudentDetails(int studentID) {
    Student student(studentID, "", "");
    std::string input;

    clearInputBuffer();
    
    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    student.setFirstName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    student.setLastName(input);

    std::cout << "Enter date of birth (DD/MM/YYYY): ";
    std::getline(std::cin, input);
    student.setDOB(input);

    std::cout << "Enter gender (M/F): ";
    std::getline(std::cin, input);
    student.setGender(input);

    std::cout << "Enter email: ";
    std::getline(std::cin, input);
    student.setEmail(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    student.setPhoneNumber(input);

    std::cout << "Enter address: ";
    std::getline(std::cin, input);
    student.setAddress(input);

    return student;
}

int main() {
    StudentManagement system;
    int choice;

    // Try to load existing data
    system.loadAllStudentsFromFile();

    do {
        displayMenu();
        std::cin >> choice;
        clearInputBuffer();

        try {
            switch (choice) {
                case 1: { // Add Student
                    Student newStudent = inputStudentDetails(system.generateUniqueID());
                    if (system.addStudent(newStudent)) {
                        std::cout << "Student added successfully." << std::endl;
                    } else {
                        std::cout << "Failed to add student." << std::endl;
                    }
                    break;
                }
                case 2: { // Update Student
                    int id;
                    std::cout << "Enter student ID to update: ";
                    std::cin >> id;
                    if (system.updateStudent(id)) {
                        std::cout << "Student updated successfully." << std::endl;
                    } else {
                        std::cout << "Student not found." << std::endl;
                    }
                    break;
                }
                case 3: { // Delete Student
                    int id;
                    std::cout << "Enter student ID to delete: ";
                    std::cin >> id;
                    if (system.deleteStudent(id)) {
                        std::cout << "Student deleted successfully." << std::endl;
                    } else {
                        std::cout << "Student not found." << std::endl;
                    }
                    break;
                }
                case 4: { // View Student Details
                    int id;
                    std::cout << "Enter student ID: ";
                    std::cin >> id;
                    system.viewStudentDetails(id);
                    break;
                }
                case 5: { // Search by Name
                    std::string name;
                    std::cout << "Enter name to search: ";
                    std::getline(std::cin, name);
                    auto results = system.searchStudentByName(name);
                    if (results.empty()) {
                        std::cout << "No students found." << std::endl;
                    } else {
                        for (const auto& student : results) {
                            student.displayStudentDetails();
                        }
                    }
                    break;
                }
                case 6: // Display All Students
                    system.displayAllStudents();
                    break;
                case 7: // Generate Report
                    system.generateReport();
                    break;
                case 8: // Calculate Class Rankings
                    system.calculateClassRanks();
                    break;
                case 9: // Save Data
                    if (system.saveAllStudentsToFile()) {
                        std::cout << "Data saved successfully." << std::endl;
                    } else {
                        std::cout << "Failed to save data." << std::endl;
                    }
                    break;
                case 10: // Load Data
                    if (system.loadAllStudentsFromFile()) {
                        std::cout << "Data loaded successfully." << std::endl;
                    } else {
                        std::cout << "Failed to load data." << std::endl;
                    }
                    break;
                case 0: // Exit
                    std::cout << "Goodbye!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

    } while (choice != 0);

    return 0;
} 