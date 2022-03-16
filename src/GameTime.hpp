#pragma once

#include "SFML/Graphics.hpp"

class GameTime {
public:
    explicit GameTime(float delay) : timer_(0.f), delay_(delay) {

    }

    GameTime(const GameTime&) = default;

    GameTime(GameTime&&) = default;

    GameTime& operator=(const GameTime&) = default;

    GameTime& operator=(GameTime&&) = default;

    void Update() {
        const auto time = this->clock_.getElapsedTime().asSeconds();

        this->clock_.restart();
        this->timer_ += time;
    }

    [[nodiscard]] bool CheckDelay() const {
        return this->timer_ >= this->delay_;
    }

    void Reset() {
        this->timer_ = 0.f;
    }

private:
    sf::Clock clock_;
    float timer_;
    float delay_;
};
