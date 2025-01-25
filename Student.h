#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

class Student {
private:
    int studentID;
    std::string firstName;
    std::string lastName;
    std::string dob;
    std::string gender;
    std::string email;
    std::string phoneNumber;
    std::string address;
    std::vector<double> marks;
    double totalMarks;
    double percentage;
    char grade;

public:
    // Constructors
    Student() : studentID(0), totalMarks(0), percentage(0), grade('F') {}
    Student(int id, const std::string& fname, const std::string& lname);

    // Getters
    int getStudentID() const { return studentID; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getDOB() const { return dob; }
    std::string getGender() const { return gender; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getAddress() const { return address; }
    char getGrade() const { return grade; }
    double getPercentage() const { return percentage; }
    double getTotalMarks() const { return totalMarks; }
    const std::vector<double>& getMarks() const { return marks; }

    // Setters
    void setStudentID(int id) { studentID = id; }
    void setFirstName(const std::string& fname) { firstName = fname; }
    void setLastName(const std::string& lname) { lastName = lname; }
    void setDOB(const std::string& birth) { dob = birth; }
    void setGender(const std::string& g) { gender = g; }
    void setEmail(const std::string& mail) { email = mail; }
    void setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
    void setAddress(const std::string& addr) { address = addr; }

    // Member functions
    void addMarks(double mark);
    void calculateGrade();
    void displayStudentDetails() const;
    void displayMarks() const;
    void calculateTotalMarks();
    void calculatePercentage();
    bool saveStudentToFile() const;
    bool loadStudentFromFile(int id);
}; 