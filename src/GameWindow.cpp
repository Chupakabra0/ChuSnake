#include "GameWindow.hpp"

void GameWindow::LaunchGameLoop() {
    while (this->renderWindow_->isOpen()) {
        this->time_->Update();

        sf::Event event{};

        while (this->renderWindow_->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->renderWindow_->close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->direction_ != SnakeDirection::DOWN) {
            this->direction_ = SnakeDirection::UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->direction_ != SnakeDirection::LEFT) {
            this->direction_ = SnakeDirection::RIGHT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->direction_ != SnakeDirection::UP) {
            this->direction_ = SnakeDirection::DOWN;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->direction_ != SnakeDirection::RIGHT) {
            this->direction_ = SnakeDirection::LEFT;
        }

        switch (this->UpdateGame()) {
            case 0: {
                //
                break;
            }
            case 1: {
                //
                return;
            }
            case 2: {
                //
                return;
            }
            default: {
                throw std::runtime_error("Unsupported int");
            }
        }
    }
}

// TODO: remove int
// 0 - continue
// 1 - loss
// 2 - win
int GameWindow::UpdateGame() {
    auto returnCode = 0;
    auto isSegmentAdded = false;

    this->renderWindow_->clear();

    // TODO: game tick method
    if (this->time_->CheckDelay()) {
        this->time_->Reset();
        this->snake_->Move(this->direction_);

        if (this->IsLoss()) {
            std::cout << "Lession(\n";
            returnCode = 1;
        }

        if (this->snake_->CheckFront({ .x = this->apple_->GetX(), .y = this->apple_->GetY() })) {
            this->snake_->AddSegment(this->apple_->GetX(), this->apple_->GetY());
            isSegmentAdded = true;
        }
    }

    this->DrawGameBoard();
    this->DrawSnake();
    this->DrawApple();

    this->renderWindow_->display();

    if (this->IsWin()) {
        std::cout << "Victory!\n";
        returnCode = 2;
    }

    if (isSegmentAdded) {
        this->apple_->GenerateApple(this->snake_, this->gameBoard_->GetWidth(), this->gameBoard_->GetHeight());
    }

    return returnCode;
}

void GameWindow::DrawGameBoard() {
    for (auto i = 0; i < this->gameBoard_->GetHeight(); ++i) {
        for (auto j = 0; j < this->gameBoard_->GetWidth(); ++j) {
            sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(GameVars::CELL_SIZE),
                                                      static_cast<float>(GameVars::CELL_SIZE)));

            rectangle.setFillColor(sf::Color::Black);
            rectangle.setOutlineThickness(GameVars::CELL_THICKNESS);
            rectangle.setOutlineColor(sf::Color::White);

            rectangle.setPosition(sf::Vector2f(static_cast<float>(j * GameVars::CELL_SIZE +
                                                                  GameVars::CELL_THICKNESS),
                                               static_cast<float>(i * GameVars::CELL_SIZE +
                                                                  GameVars::CELL_THICKNESS)));

            this->renderWindow_->draw(rectangle);
        }
    }
}

void GameWindow::DrawSnake() {
    auto begin = this->snake_->GetSegments().begin();
    auto end   = std::next(begin, static_cast<int>(this->snake_->GetSize()));

    for (; begin != end; ++begin) {
        sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(GameVars::CELL_SIZE),
                                                  static_cast<float>(GameVars::CELL_SIZE)));

        rectangle.setFillColor(sf::Color::Green);
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(sf::Color::Green);

        rectangle.setPosition(sf::Vector2f(static_cast<float>(begin->x * GameVars::CELL_SIZE +
                                                              GameVars::CELL_THICKNESS),
                                           static_cast<float>(begin->y * GameVars::CELL_SIZE +
                                                              GameVars::CELL_THICKNESS)));

        this->renderWindow_->draw(rectangle);
    }
}

void GameWindow::DrawApple() {
    sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(GameVars::CELL_SIZE),
                                              static_cast<float>(GameVars::CELL_SIZE)));

    rectangle.setFillColor(sf::Color::Red);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color::Red);

    rectangle.setPosition(sf::Vector2f(static_cast<float>(this->apple_->GetX() * GameVars::CELL_SIZE +
                                                          GameVars::CELL_THICKNESS),
                                       static_cast<float>(this->apple_->GetY() * GameVars::CELL_SIZE +
                                                          GameVars::CELL_THICKNESS)));

    this->renderWindow_->draw(rectangle);
}

bool GameWindow::IsWin() {
    return this->snake_->GetSize() >= this->snake_->GetSegments().size();
}

bool GameWindow::IsLoss() {
    return this->snake_->IsTouchedItself();
}

int GameWindow::GetCellSize() const {
    return this->cellSize_;
}

int GameWindow::GetHeight() const {
    return this->height_;
}

int GameWindow::GetWidth() const {
    return this->width_;
}
