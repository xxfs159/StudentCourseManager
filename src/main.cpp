#include "StudentManager.h"
#include "Storage.h"

#include <iomanip>
#include <iostream>
#include <limits>

void clearInput();

namespace {
const std::string kDataFilePath = "data/students.json";

bool readInt(const std::string& prompt, int& value) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
        clearInput();
        return false;
    }

    clearInput();
    return true;
}

bool readText(const std::string& prompt, std::string& value) {
    std::cout << prompt;
    std::getline(std::cin, value);
    return !value.empty();
}

void printStudent(const Student& student) {
    std::cout << "ID: " << student.getId()
              << ", Name: " << student.getName()
              << ", Age: " << student.getAge()
              << ", Major: " << student.getMajor()
              << '\n';
}

void printCourse(const Course& course) {
    std::cout << "ID: " << course.getId()
              << ", Name: " << course.getName()
              << ", Credit: " << course.getCredit()
              << '\n';
}

void printStudents(const StudentManager& manager) {
    const auto& students = manager.getAllStudents();
    if (students.empty()) {
        std::cout << "No students.\n";
        return;
    }

    for (const auto& student : students) {
        printStudent(student);
    }
}

void saveStudentsOrReport(const StudentManager& manager) {
    if (!Storage::saveData(manager, kDataFilePath)) {
        std::cout << "Warning: failed to save data to " << kDataFilePath << "\n";
    }
}
}  // namespace

void printMenu() {
    std::cout << "\n===== Student Course Manager =====\n";
    std::cout << "1. Add student\n";
    std::cout << "2. List students\n";
    std::cout << "3. Find student\n";
    std::cout << "4. Update student\n";
    std::cout << "5. Remove student\n";
    std::cout << "6. Add course\n";
    std::cout << "7. Add grade\n";
    std::cout << "8. Show course average\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    StudentManager manager;

    if (!Storage::loadData(manager, kDataFilePath)) {
        std::cout << "Starting with an empty student list.\n";
    }

    while (true) {
        printMenu();

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        if (choice == 0) {
            break;
        }

        try {
            if (choice == 1) {
                int id;
                std::string name;
                int age;
                std::string major;

                if (!readInt("ID: ", id)) {
                    std::cout << "Invalid ID.\n";
                    continue;
                }

                if (!readText("Name: ", name)) {
                    std::cout << "Name cannot be empty.\n";
                    continue;
                }

                if (!readInt("Age: ", age)) {
                    std::cout << "Invalid age.\n";
                    continue;
                }

                if (!readText("Major: ", major)) {
                    std::cout << "Major cannot be empty.\n";
                    continue;
                }

                manager.addStudent(Student{id, name, age, major});
                std::cout << "Student added.\n";
                saveStudentsOrReport(manager);
            } else if (choice == 2) {
                printStudents(manager);
            } else if (choice == 3) {
                int id;
                if (!readInt("ID: ", id)) {
                    std::cout << "Invalid ID.\n";
                    continue;
                }

                auto student = manager.findStudentById(id);

                if (student.has_value()) {
                    printStudent(*student);
                } else {
                    std::cout << "Student not found.\n";
                }
            } else if (choice == 4) {
                int id;
                std::string name;
                int age;
                std::string major;

                if (!readInt("ID: ", id)) {
                    std::cout << "Invalid ID.\n";
                    continue;
                }

                if (!readText("New name: ", name)) {
                    std::cout << "Name cannot be empty.\n";
                    continue;
                }

                if (!readInt("New age: ", age)) {
                    std::cout << "Invalid age.\n";
                    continue;
                }

                if (!readText("New major: ", major)) {
                    std::cout << "Major cannot be empty.\n";
                    continue;
                }

                if (manager.updateStudent(id, name, age, major)) {
                    std::cout << "Student updated.\n";
                    saveStudentsOrReport(manager);
                } else {
                    std::cout << "Student not found.\n";
                }
            } else if (choice == 5) {
                int id;
                if (!readInt("ID: ", id)) {
                    std::cout << "Invalid ID.\n";
                    continue;
                }

                if (manager.removeStudentById(id)) {
                    std::cout << "Student removed.\n";
                    saveStudentsOrReport(manager);
                } else {
                    std::cout << "Student not found.\n";
                }
            } else if (choice == 6) {
                int courseId;
                std::string courseName;
                int credit;

                if (!readInt("Course ID: ", courseId)) {
                    std::cout << "Invalid course ID.\n";
                    continue;
                }

                if (!readText("Course name: ", courseName)) {
                    std::cout << "Course name cannot be empty.\n";
                    continue;
                }

                if (!readInt("Credit: ", credit)) {
                    std::cout << "Invalid credit.\n";
                    continue;
                }

                manager.addCourse(Course{courseId, courseName, credit});
                std::cout << "Course added.\n";
                saveStudentsOrReport(manager);
            } else if (choice == 7) {
                int studentId;
                int courseId;
                double score;

                if (!readInt("Student ID: ", studentId)) {
                    std::cout << "Invalid student ID.\n";
                    continue;
                }

                if (!readInt("Course ID: ", courseId)) {
                    std::cout << "Invalid course ID.\n";
                    continue;
                }

                std::cout << "Score (0-100): ";
                if (!(std::cin >> score)) {
                    std::cout << "Invalid score.\n";
                    clearInput();
                    continue;
                }
                clearInput();

                manager.addGrade(Grade{studentId, courseId, score});
                std::cout << "Grade added.\n";
                saveStudentsOrReport(manager);
            } else if (choice == 8) {
                int courseId;
                if (!readInt("Course ID: ", courseId)) {
                    std::cout << "Invalid course ID.\n";
                    continue;
                }

                auto course = manager.findCourseById(courseId);
                if (!course.has_value()) {
                    std::cout << "Course not found.\n";
                    continue;
                }

                auto average = manager.getCourseAverageScore(courseId);
                if (!average.has_value()) {
                    std::cout << "No grades for this course yet.\n";
                    continue;
                }

                printCourse(*course);
                std::cout << "Average score: " << std::fixed << std::setprecision(2) << *average << '\n';
            } else {
                std::cout << "Unknown choice.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    saveStudentsOrReport(manager);

    return 0;
}
