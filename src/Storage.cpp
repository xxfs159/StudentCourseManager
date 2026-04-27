#include "Storage.h"

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

Student jsonToStudent(const json& value) {
    return Student{value.at("id").get<int>(), value.at("name").get<std::string>(), value.at("age").get<int>(), value.at("major").get<std::string>()};
}
}  // namespace

bool Storage::saveStudents(const StudentManager& manager, const std::string& filePath) {
    std::ofstream output(filePath);
    if (!output) {
        return false;
    }

    json data = json::array();
    for (const auto& student : manager.getAllStudents()) {
        data.push_back(studentToJson(student));
    }

    output << data.dump(4);
    return static_cast<bool>(output);
}

bool Storage::loadStudents(StudentManager& manager, const std::string& filePath) {
    std::ifstream input(filePath);
    if (!input) {
        return false;
    }

    try {
        json data;
        input >> data;

        if (!data.is_array()) {
            return false;
        }

        StudentManager loadedStudents;
        for (const auto& item : data) {
            loadedStudents.addStudent(jsonToStudent(item));
        }

        manager = std::move(loadedStudents);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}
