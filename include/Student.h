#pragma once

#include <string>

class Student {
private:
    int id_{};
    std::string name_;
    int age_{};
    std::string major_;

public:
    Student() = default;
    Student(int id, std::string name, int age, std::string major);

    int getId() const;
    const std::string& getName() const;
    int getAge() const;
    const std::string& getMajor() const;

    void setName(const std::string& name);
    void setAge(int age);
    void setMajor(const std::string& major);
};
