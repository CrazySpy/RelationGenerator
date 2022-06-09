//
// Created by jiang on 2022/5/27.
//

#include "Utils.h"
#include "Types.h"

double euclidDistance(const LocationType &location1, const LocationType &location2) {
    return std::sqrt(std::pow(location1.first - location2.first, 2) + std::pow(location1.second - location2.second, 2));
}

double doubleEqual(double num1, double num2) {
    return num1 == num2 || std::fabs(num1 - num2) < 1e-6;
}