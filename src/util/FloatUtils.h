#pragma once

#include <cmath>

#define EPSILON 0.00005f

namespace FloatUtils {

    static bool compare(float a, float b) {
        return std::abs(a - b) < EPSILON;
    }

}