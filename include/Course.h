#pragma once

#include <string>

class Course {
private:
    int id_{};
    std::string name_;
    int credit_{};

public:
    Course() = default;
    Course(int id, std::string name, int credit);

    int getId() const;
    const std::string& getName() const;
    int getCredit() const;
};
