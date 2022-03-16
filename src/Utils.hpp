#pragma once

#include <random>

// TODO: singleton
inline static std::mt19937 generator{};

inline int RandInt(int low, int high) {
    std::uniform_int_distribution uid(low, high);
    return uid(generator);
}
