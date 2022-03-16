#pragma once

#include <algorithm>

#include "Snake.hpp"
#include "Utils.hpp"

class Apple {
public:
    explicit Apple(int x = 0, int y = 0) : x_(x), y_(y) {

    }

    Apple(const Apple&) = default;

    Apple(Apple&&) = default;

    Apple& operator=(const Apple&) = default;

    Apple& operator=(Apple&&) = default;

    [[nodiscard]] int GetX() const {
        return this->x_;
    }

    [[nodiscard]] int GetY() const {
        return this->y_;
    }

    void GenerateApple(const std::shared_ptr<Snake>& snake, int x, int y) {
        auto xTemp = RandInt(0, x - 1);
        auto yTemp = RandInt(0, y - 1);

        const auto seg  = snake->GetSegments();
        const auto temp = SnakeSegment{.x = xTemp, .y = yTemp};

        if (std::find(seg.begin(), seg.end(), temp) != seg.end()) {
            return GenerateApple(snake, x, y);
        }

        this->x_ = xTemp;
        this->y_ = yTemp;
    }

private:
    int x_;
    int y_;
};
