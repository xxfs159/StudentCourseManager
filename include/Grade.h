#pragma once

class Grade {
private:
    int studentId_{};
    int courseId_{};
    double score_{};

public:
    Grade() = default;
    Grade(int studentId, int courseId, double score);

    int getStudentId() const;
    int getCourseId() const;
    double getScore() const;

    void setScore(double score);
};
