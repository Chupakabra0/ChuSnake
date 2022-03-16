#include "Snake.hpp"

#include "GameVars.hpp"

int Snake::GetSize() const {
    return this->size_;
}

const std::vector<SnakeSegment> &Snake::GetSegments() const {
    return this->segments_;
}

void Snake::AddSegment(int x, int y) {
    *std::next(this->segments_.begin(), this->size_) = { .x = x, .y = y };
    ++this->size_;
}

void Snake::Move(SnakeDirection direction) {
    std::cout << fmt::format("Snake size: {}\n", this->size_);

    for (auto i = this->size_ - 1; i > 0; --i) {
        this->segments_[i] = this->segments_[i - 1];
    }

    auto& front = this->segments_.front();

    switch (direction) {
        case SnakeDirection::NONE: {
            break;
        }
        case SnakeDirection::UP: {
            front.y -= 1;

            if (front.y < 0) {
                front.y = GameVars::BOARD_HEIGHT - 1;
            }

            break;
        }
        case SnakeDirection::RIGHT: {
            front.x += 1;

            if (front.x > GameVars::BOARD_WIDTH - 1) {
                front.x = 0;
            }

            break;
        }
        case SnakeDirection::DOWN: {
            front.y += 1;

            if (front.y > GameVars::BOARD_HEIGHT - 1) {
                front.y = 0;
            }

            break;
        }
        case SnakeDirection::LEFT: {
            front.x -= 1;

            if (front.x < 0) {
                front.x = GameVars::BOARD_WIDTH - 1;
            }

            break;
        }
        default: {
            throw std::runtime_error("Unsupported direction move");
        }
    }
}

bool Snake::CheckFront(SnakeSegment s) const {
    return s == this->segments_.front();
}

bool Snake::IsTouchedItself() {
    return this->size_ > 3 && std::find_if(std::next(this->segments_.begin()),
                                           std::next(this->segments_.begin(), this->size_),
                                           [this](const auto& s)  {
                                               return s == this->segments_.front();
                                           }
    ) != std::next(this->segments_.begin(), this->size_);
}
