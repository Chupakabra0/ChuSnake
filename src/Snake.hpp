#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "fmt/format.h"

enum class SnakeDirection : short {
    NONE = 0, UP, RIGHT, DOWN, LEFT
};

struct SnakeSegment {
    int x;
    int y;

    friend bool operator==(const SnakeSegment& first, const SnakeSegment& second) {
        return first.x == second.x && first.y == second.y;
    }

    friend bool operator!=(const SnakeSegment& first, const SnakeSegment& second) {
        return !(first == second);
    }
};

class Snake {
public:
    explicit Snake(int x, int y, int maxSize) : size_(0), segments_(maxSize, { .x = -1, .y = -1 }) {
        this->AddSegment(x, y);
        this->AddSegment(x, y);
        this->AddSegment(x, y);
    }

    Snake(const Snake&) = default;

    Snake(Snake&&) = default;

    ~Snake() = default;

    Snake& operator=(const Snake&) = default;

    Snake& operator=(Snake&&) = default;

    [[nodiscard]] int GetSize() const;

    [[nodiscard]] const std::vector<SnakeSegment>& GetSegments() const;

    void AddSegment(int x, int y);

    void Move(SnakeDirection direction);

    [[nodiscard]] bool CheckFront(SnakeSegment s) const;

    [[nodiscard]] bool IsTouchedItself();

private:
    int size_;
    std::vector<SnakeSegment> segments_;
};