#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

class GameBoard {
public:
    explicit GameBoard(int heightAndWidth);

    explicit GameBoard(int height, int width) : height_(height), width_(width) {

    }

    GameBoard(const GameBoard&) = default;

    GameBoard(GameBoard&&) = default;

    ~GameBoard() = default;

    GameBoard& operator=(const GameBoard&) = default;

    GameBoard& operator=(GameBoard&&) = default;

    [[nodiscard]] int GetHeight() const {
        return this->height_;
    }

    [[nodiscard]] int GetWidth() const {
        return this->width_;
    }

private:
    int height_;
    int width_;
};
