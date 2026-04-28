#include "StudentManager.h"
#include "Storage.h"

#include <cassert>
#include <filesystem>
#include <stdexcept>

namespace {
std::filesystem::path makeTempFilePath() {
    auto path = std::filesystem::temp_directory_path() / "student_course_manager_roundtrip.json";
    std::error_code errorCode;
    std::filesystem::remove(path, errorCode);
    return path;
}
}  // namespace

int main() {
    StudentManager manager;

    manager.addStudent(Student{1, "Alice", 20, "CS"});
    manager.addStudent(Student{2, "Bob", 21, "Math"});
    manager.addCourse(Course{100, "Algorithms", 4});
    manager.addCourse(Course{200, "Databases", 3});
    manager.addGrade(Grade{1, 100, 95.0});
    manager.addGrade(Grade{2, 100, 85.0});

    bool invalidIdRejected = false;
    try {
        manager.addStudent(Student{0, "Invalid", 20, "CS"});
    } catch (const std::invalid_argument&) {
        invalidIdRejected = true;
    }
    assert(invalidIdRejected);

    bool invalidAgeRejected = false;
    try {
        manager.addStudent(Student{3, "Invalid", -1, "CS"});
    } catch (const std::invalid_argument&) {
        invalidAgeRejected = true;
    }
    assert(invalidAgeRejected);

    assert(manager.getAllStudents().size() == 2);
    assert(manager.exists(1));
    assert(manager.findStudentById(2).has_value());
    assert(manager.courseExists(100));
    assert(manager.findCourseById(200).has_value());

    auto average = manager.getCourseAverageScore(100);
    assert(average.has_value());
    assert(*average == 90.0);
    assert(!manager.getCourseAverageScore(200).has_value());

    assert(manager.updateStudent(1, "Alicia", 22, "SE"));
    auto updated = manager.findStudentById(1);
    assert(updated.has_value());
    assert(updated->getName() == "Alicia");
    assert(updated->getAge() == 22);
    assert(updated->getMajor() == "SE");

    assert(manager.removeStudentById(2));
    assert(!manager.exists(2));

    const auto tempFilePath = makeTempFilePath();
    assert(Storage::saveStudents(manager, tempFilePath.string()));

    StudentManager loadedManager;
    assert(Storage::loadStudents(loadedManager, tempFilePath.string()));
    assert(loadedManager.getAllStudents().size() == 1);
    assert(loadedManager.exists(1));
    assert(loadedManager.courseExists(100));
    auto loadedAverage = loadedManager.getCourseAverageScore(100);
    assert(loadedAverage.has_value());
    assert(*loadedAverage == 95.0);
    auto loaded = loadedManager.findStudentById(1);
    assert(loaded.has_value());
    assert(loaded->getName() == "Alicia");

    std::filesystem::remove(tempFilePath);

    return 0;
}
