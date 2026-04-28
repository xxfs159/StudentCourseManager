#include "Storage.h"

#include "Course.h"
#include "Grade.h"
#include "Student.h"

#include <exception>
#include <fstream>
#include <utility>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {
json studentToJson(const Student& student) {
    return json{{"id", student.getId()}, {"name", student.getName()}, {"age", student.getAge()}, {"major", student.getMajor()}};
}

json courseToJson(const Course& course) {
    return json{{"id", course.getId()}, {"name", course.getName()}, {"credit", course.getCredit()}};
}

json gradeToJson(const Grade& grade) {
    return json{{"studentId", grade.getStudentId()}, {"courseId", grade.getCourseId()}, {"score", grade.getScore()}};
}

Student jsonToStudent(const json& value) {
    return Student{value.at("id").get<int>(), value.at("name").get<std::string>(), value.at("age").get<int>(), value.at("major").get<std::string>()};
}

Course jsonToCourse(const json& value) {
    return Course{value.at("id").get<int>(), value.at("name").get<std::string>(), value.at("credit").get<int>()};
}

Grade jsonToGrade(const json& value) {
    return Grade{value.at("studentId").get<int>(), value.at("courseId").get<int>(), value.at("score").get<double>()};
}
}  // namespace

bool Storage::saveData(const StudentManager& manager, const std::string& filePath) {
    std::ofstream output(filePath);
    if (!output) {
        return false;
    }

    json students = json::array();
    for (const auto& student : manager.getAllStudents()) {
        students.push_back(studentToJson(student));
    }

    json courses = json::array();
    for (const auto& course : manager.getAllCourses()) {
        courses.push_back(courseToJson(course));
    }

    json grades = json::array();
    for (const auto& grade : manager.getAllGrades()) {
        grades.push_back(gradeToJson(grade));
    }

    json data = {
        {"students", students},
        {"courses", courses},
        {"grades", grades},
    };

    output << data.dump(4);
    return static_cast<bool>(output);
}

bool Storage::loadData(StudentManager& manager, const std::string& filePath) {
    std::ifstream input(filePath);
    if (!input) {
        return false;
    }

    try {
        json data;
        input >> data;

        StudentManager loadedStudents;

        if (data.is_array()) {
            for (const auto& item : data) {
                loadedStudents.addStudent(jsonToStudent(item));
            }

            manager = std::move(loadedStudents);
            return true;
        }

        if (!data.is_object()) {
            return false;
        }

        if (!data.contains("students") || !data["students"].is_array()) {
            return false;
        }

        for (const auto& item : data["students"]) {
            loadedStudents.addStudent(jsonToStudent(item));
        }

        if (data.contains("courses")) {
            if (!data["courses"].is_array()) {
                return false;
            }

            for (const auto& item : data["courses"]) {
                loadedStudents.addCourse(jsonToCourse(item));
            }
        }

        if (data.contains("grades")) {
            if (!data["grades"].is_array()) {
                return false;
            }

            for (const auto& item : data["grades"]) {
                loadedStudents.addGrade(jsonToGrade(item));
            }
        }

        manager = std::move(loadedStudents);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool Storage::saveStudents(const StudentManager& manager, const std::string& filePath) {
    return saveData(manager, filePath);
}

bool Storage::loadStudents(StudentManager& manager, const std::string& filePath) {
    return loadData(manager, filePath);
}
