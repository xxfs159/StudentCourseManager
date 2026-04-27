#pragma once

#include "StudentManager.h"

#include <string>

class Storage {
public:
    static bool saveStudents(const StudentManager& manager, const std::string& filePath);
    static bool loadStudents(StudentManager& manager, const std::string& filePath);
};
