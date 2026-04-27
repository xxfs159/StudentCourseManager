#include "StudentManager.h"

#include <algorithm>
#include <stdexcept>

void StudentManager::addStudent(const Student& student) {
    if (exists(student.getId())) {
        throw std::runtime_error("Student ID already exists.");
    }

    students_.push_back(student);
}

bool StudentManager::removeStudentById(int id) {
    auto it = std::find_if(students_.begin(), students_.end(), [id](const Student& student) {
        return student.getId() == id;
    });

    if (it == students_.end()) {
        return false;
    }

    students_.erase(it);
    return true;
}

bool StudentManager::updateStudent(int id, const std::string& name, int age, const std::string& major) {
    for (auto& student : students_) {
        if (student.getId() == id) {
            student.setName(name);
            student.setAge(age);
            student.setMajor(major);
            return true;
        }
    }

    return false;
}

std::optional<Student> StudentManager::findStudentById(int id) const {
    auto it = std::find_if(students_.begin(), students_.end(), [id](const Student& student) {
        return student.getId() == id;
    });

    if (it != students_.end()) {
        return *it;
    }

    return std::nullopt;
}

const std::vector<Student>& StudentManager::getAllStudents() const {
    return students_;
}

bool StudentManager::exists(int id) const {
    return std::any_of(students_.begin(), students_.end(), [id](const Student& student) {
        return student.getId() == id;
    });
}
