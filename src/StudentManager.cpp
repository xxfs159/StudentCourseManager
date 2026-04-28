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
    grades_.erase(
        std::remove_if(grades_.begin(), grades_.end(), [id](const Grade& grade) {
            return grade.getStudentId() == id;
        }),
        grades_.end());
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

void StudentManager::addCourse(const Course& course) {
    if (courseExists(course.getId())) {
        throw std::runtime_error("Course ID already exists.");
    }

    courses_.push_back(course);
}

std::optional<Course> StudentManager::findCourseById(int id) const {
    auto it = std::find_if(courses_.begin(), courses_.end(), [id](const Course& course) {
        return course.getId() == id;
    });

    if (it != courses_.end()) {
        return *it;
    }

    return std::nullopt;
}

const std::vector<Course>& StudentManager::getAllCourses() const {
    return courses_;
}

void StudentManager::addGrade(const Grade& grade) {
    if (!exists(grade.getStudentId())) {
        throw std::runtime_error("Student does not exist.");
    }

    if (!courseExists(grade.getCourseId())) {
        throw std::runtime_error("Course does not exist.");
    }

    if (grade.getScore() < 0.0 || grade.getScore() > 100.0) {
        throw std::runtime_error("Score must be between 0 and 100.");
    }

    grades_.push_back(grade);
}

const std::vector<Grade>& StudentManager::getAllGrades() const {
    return grades_;
}

std::optional<double> StudentManager::getCourseAverageScore(int courseId) const {
    double total = 0.0;
    std::size_t count = 0;

    for (const auto& grade : grades_) {
        if (grade.getCourseId() == courseId) {
            total += grade.getScore();
            ++count;
        }
    }

    if (count == 0) {
        return std::nullopt;
    }

    return total / static_cast<double>(count);
}

bool StudentManager::exists(int id) const {
    return std::any_of(students_.begin(), students_.end(), [id](const Student& student) {
        return student.getId() == id;
    });
}

bool StudentManager::courseExists(int id) const {
    return std::any_of(courses_.begin(), courses_.end(), [id](const Course& course) {
        return course.getId() == id;
    });
}
