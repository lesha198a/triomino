#include <iostream>

#include "Board.h"


int main() {
    auto board = Board::createBoard();
    std::cout << board << std::endl;
    board.run();
    return 0;
}
