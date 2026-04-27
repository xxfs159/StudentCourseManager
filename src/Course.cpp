#include "Course.h"

#include <utility>

Course::Course(int id, std::string name, int credit)
    : id_(id), name_(std::move(name)), credit_(credit) {}

int Course::getId() const {
    return id_;
}

const std::string& Course::getName() const {
    return name_;
}

int Course::getCredit() const {
    return credit_;
}
