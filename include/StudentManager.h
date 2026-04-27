#pragma once

#include "Student.h"

#include <optional>
#include <string>
#include <vector>

class StudentManager {
private:
    std::vector<Student> students_;

public:
    void addStudent(const Student& student);
    bool removeStudentById(int id);
    bool updateStudent(int id, const std::string& name, int age, const std::string& major);

    std::optional<Student> findStudentById(int id) const;
    const std::vector<Student>& getAllStudents() const;

    bool exists(int id) const;
};
