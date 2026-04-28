#pragma once

#include "Course.h"
#include "Grade.h"
#include "Student.h"

#include <optional>
#include <string>
#include <vector>

class StudentManager {
private:
    std::vector<Student> students_;
    std::vector<Course> courses_;
    std::vector<Grade> grades_;

public:
    void addStudent(const Student& student);
    bool removeStudentById(int id);
    bool updateStudent(int id, const std::string& name, int age, const std::string& major);

    std::optional<Student> findStudentById(int id) const;
    const std::vector<Student>& getAllStudents() const;

    void addCourse(const Course& course);
    std::optional<Course> findCourseById(int id) const;
    const std::vector<Course>& getAllCourses() const;

    void addGrade(const Grade& grade);
    const std::vector<Grade>& getAllGrades() const;
    std::optional<double> getCourseAverageScore(int courseId) const;

    bool exists(int id) const;
    bool courseExists(int id) const;
};
