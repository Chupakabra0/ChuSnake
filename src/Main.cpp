#include <fmt/format.h>

#include "GameWindow.hpp"
#include "GameVars.hpp"

int main() {
    try {
        auto gameBoard = std::make_shared<GameBoard>(GameVars::BOARD_HEIGHT, GameVars::BOARD_WIDTH);
        auto gameWindow = std::make_shared<GameWindow>(gameBoard, "Dev", GameVars::CELL_SIZE);

        gameWindow->LaunchGameLoop();
    }
    catch (const std::exception& exception) {
        std::cout << fmt::format("Exception: {}\n", exception.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}