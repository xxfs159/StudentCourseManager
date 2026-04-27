cmake_minimum_required(VERSION 3.20)

project(StudentCourseManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
include(CTest)

# 引入 nlohmann/json，用来读写 JSON 文件

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# 主程序
add_executable(StudentCourseManager
    src/main.cpp
    src/Student.cpp
    src/Course.cpp
    src/Grade.cpp
    src/StudentManager.cpp
    src/Storage.cpp
)

target_include_directories(StudentCourseManager PRIVATE include)

target_link_libraries(StudentCourseManager PRIVATE nlohmann_json::nlohmann_json)

add_executable(StudentCourseManagerTests
    tests/test_student_manager.cpp
    src/Student.cpp
    src/StudentManager.cpp
    src/Storage.cpp
)

target_include_directories(StudentCourseManagerTests PRIVATE include)
target_link_libraries(StudentCourseManagerTests PRIVATE nlohmann_json::nlohmann_json)

if(BUILD_TESTING)
    add_test(NAME StudentManagerTests COMMAND StudentCourseManagerTests)
endif()