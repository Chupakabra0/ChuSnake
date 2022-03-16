#pragma once
#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "GameBoard.hpp"
#include "GameVars.hpp"
#include "GameTime.hpp"
#include "Snake.hpp"
#include "Apple.hpp"

class GameWindow {
public:
    explicit GameWindow(const std::shared_ptr<GameBoard>& gameBoard, const std::string& windowName, int cellSize) :
        cellSize_(cellSize), height_(gameBoard->GetHeight() * cellSize), width_(gameBoard->GetWidth() * cellSize),
        gameBoard_(gameBoard), renderWindow_(new sf::RenderWindow(
                sf::VideoMode(this->width_ + GameVars::CELL_THICKNESS * 2,
                              this->height_ + GameVars::CELL_THICKNESS * 2),
                  windowName,sf::Style::Close)),
        snake_(new Snake(gameBoard->GetWidth() / 2, gameBoard->GetHeight() / 2,
                         gameBoard->GetHeight() * gameBoard->GetWidth())),
        apple_(new Apple), time_(new GameTime(GameVars::GAME_DELAY)) {
        this->apple_->GenerateApple(this->snake_, this->gameBoard_->GetWidth() - 1, this->gameBoard_->GetHeight() - 1);
    }

    GameWindow(const GameWindow&) = default;

    GameWindow(GameWindow&&) = default;

    ~GameWindow() = default;

    GameWindow& operator=(const GameWindow&) = default;

    GameWindow& operator=(GameWindow&&) = default;

    [[nodiscard]] int GetCellSize() const;

    [[nodiscard]] int GetHeight() const;

    [[nodiscard]] int GetWidth() const;

    void LaunchGameLoop();

private:
    SnakeDirection direction_ = SnakeDirection::NONE;
    int cellSize_;
    int height_;
    int width_;
    std::shared_ptr<GameBoard> gameBoard_;
    std::shared_ptr<sf::RenderWindow> renderWindow_;
    std::shared_ptr<Snake> snake_;
    std::shared_ptr<Apple> apple_;
    std::shared_ptr<GameTime> time_;

    int UpdateGame();

    void DrawGameBoard();

    void DrawSnake();

    void DrawApple();

    [[nodiscard]] bool IsWin();

    [[nodiscard]] bool IsLoss();
};
