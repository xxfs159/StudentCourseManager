#include "Grade.h"

Grade::Grade(int studentId, int courseId, double score)
    : studentId_(studentId), courseId_(courseId), score_(score) {}

int Grade::getStudentId() const {
    return studentId_;
}

int Grade::getCourseId() const {
    return courseId_;
}

double Grade::getScore() const {
    return score_;
}

void Grade::setScore(double score) {
    score_ = score;
}
