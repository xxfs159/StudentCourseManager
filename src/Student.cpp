#include "Student.h"

#include <stdexcept>
#include <utility>

Student::Student(int id, std::string name, int age, std::string major)
    : id_(id), name_(std::move(name)), major_(std::move(major)) {
    if (id_ <= 0) {
        throw std::invalid_argument("Student ID must be positive.");
    }

    setAge(age);
}

int Student::getId() const {
    return id_;
}

const std::string& Student::getName() const {
    return name_;
}

int Student::getAge() const {
    return age_;
}

const std::string& Student::getMajor() const {
    return major_;
}

void Student::setName(const std::string& name) {
    name_ = name;
}

void Student::setAge(int age) {
    if (age <= 0) {
        throw std::invalid_argument("Student age must be positive.");
    }

    age_ = age;
}

void Student::setMajor(const std::string& major) {
    major_ = major;
}
