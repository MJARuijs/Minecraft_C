#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "../math/Color.h"

class Logger {

public:
    static void log(const std::stringstream & message) {
        std::cout << message.str() << std::endl;
    }

    static void log(const Vec3 & vector) {
        std::cout << vector.x << ", " << vector.y << ", " << vector.z << std::endl;
    }

    static void log(const Vec4 & vector) {
        std::cout << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << std::endl;
    }

    static void log(Mat4 & matrix) {
        std::cout << matrix.get(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << "\n"
        << matrix.get(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << "\n"
        << matrix.get(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << "\n"
        << matrix.get(3, 0) << ", " << matrix(3, 1) << ", " << matrix(3, 2) << ", " << matrix(3, 3) << "\n" << std::endl;
    }

    static void log(const Color & color) {
        std::cout << color.getR() << ", " << color.getG() << ", " << color.getB() << ", " << color.getA() << std::endl;
    }

    static void log(float & message) {
        std::cout << message << std::endl;
    }

    static void log(const std::string & message) {
        std::cout << message << std::endl;
    }

    static void log(std::string & message) {
        std::cout << message << std::endl;
    }

    static void err(const std::string & message) {
        std::cout << "\033[32m" << message << "\033[0m" << std::endl;
    }

    static void warn(const std::string & message) {
        std::cout << "\033[33m" << message << "\033[0m" << std::endl;
    }

    static void info(const std::string & message) {
        std::cout << "\033[34m" << message << "\033[0m" << std::endl;
    }

};
