#include "Board.h"

#include <cmath>
#include <iostream>

Board::Board(size_t n) {
    mLength = static_cast<size_t>(std::pow(2, n));

    mBoard = new bool *[mLength];

    for (int i = 0; i < mLength; ++i) {
        mBoard[i] = new bool[mLength];
        for (int j = 0; j < mLength; ++j) {
            mBoard[i][j] = false;
        }
    }
}

Board::Board(const Board &board) {
    mLength = board.mLength;

    mBoard = new bool *[mLength];

    for (int i = 0; i < mLength; ++i) {
        mBoard[i] = new bool[mLength];
        for (int j = 0; j < mLength; ++j) {
            mBoard[i][j] = board.mBoard[i][j];
        }
    }
}

Board::~Board() {
    for (int i = 0; i < mLength; ++i) {
        delete mBoard[i];
    }
    delete mBoard;
}

bool Board::setPoint(size_t x, size_t y) {
    if (x >= mLength || y >= mLength) {
        std::cout << "X or Y is bigger then 2^n\nX = " << x << "\nY = " << y << "\n2^n = " << mLength << std::endl;
        return false;
    }
    mBoard[x][y] = true;
    return true;
}

Board Board::createBoard() {
    std::cout << "\nInput unsigned integer for board sizes (2^n)" << std::endl;

    size_t n = 0, x = 0, y = 0;
    std::cin >> n;
    Board board(n);

    bool pointInputStatus = false;

    while (!pointInputStatus) {
        std::cout << "\nInput X and Y for point M(X, Y) checked on board (unsigned integers)\nX = ";
        std::cin >> x;
        std::cout << "\nY = ";
        std::cin >> y;

        pointInputStatus = board.setPoint(x, y);
    }
    return board;
}

void Board::run() {
    place({0, 0}, {mLength - 1, mLength - 1});
}

std::ostream &operator<<(std::ostream &stream, const Board &board) {
    for (int i = static_cast<int>(board.mLength) - 1; i >= 0 ; --i) {
        for (int j = 0; j < board.mLength; ++j) {
            if (board.mBoard[j][i]) {
                stream << "X|";
            } else {
                stream << "_|";
            }
        }
        stream << std::endl;
    }
    return stream;
}

void Board::place(pos leftBottom, pos rightTop) {
    if (leftBottom.X >= rightTop.X || leftBottom.Y >= rightTop.Y) {
        return;
    }

    // - 4 | - 6
    // 3 - | 5 -
    // —————————
    // - 2 | - 8
    // 1 - | 7 -

    leftBottom;//1

    pos leftBottomCenter(leftBottom.X + (rightTop.X - leftBottom.X) / 2, leftBottom.Y + (rightTop.Y - leftBottom.Y) / 2); //2

    pos thirdPos(leftBottom.X, leftBottomCenter.Y + 1);//3

    pos fourthPos(leftBottomCenter.X, rightTop.Y);//4

    pos fifthPos(leftBottomCenter.X + 1, leftBottomCenter.Y + 1);//5

    rightTop;//6

    pos seventhPos(fifthPos.X, leftBottom.Y);//7

    pos eighthPos(rightTop.X, leftBottomCenter.Y);//8


    if (check(leftBottom, leftBottomCenter)) {
        mBoard[leftBottomCenter.X + 1][leftBottomCenter.Y] = true;
        mBoard[leftBottomCenter.X + 1][leftBottomCenter.Y + 1] = true;
        mBoard[leftBottomCenter.X][leftBottomCenter.Y + 1] = true;
    } else if (check(thirdPos, fourthPos)) {
        mBoard[leftBottomCenter.X + 1][leftBottomCenter.Y] = true;
        mBoard[leftBottomCenter.X + 1][leftBottomCenter.Y + 1] = true;
        mBoard[leftBottomCenter.X][leftBottomCenter.Y] = true;
    } else if (check(fifthPos, rightTop)) {
        mBoard[leftBottomCenter.X + 1][leftBottomCenter.Y] = true;
        mBoard[leftBottomCenter.X][leftBottomCenter.Y] = true;
        mBoard[leftBottomCenter.X][leftBottomCenter.Y + 1] = true;
    } else {
        mBoard[leftBottomCenter.X][leftBottomCenter.Y] = true;
        mBoard[leftBottomCenter.X + 1][leftBottomCenter.Y + 1] = true;
        mBoard[leftBottomCenter.X][leftBottomCenter.Y + 1] = true;
    }

    std::cout << "\n\n"
              << *this << std::endl;

    place(leftBottom, leftBottomCenter);
    place(thirdPos, fourthPos);
    place(fifthPos, rightTop);
    place(seventhPos, eighthPos);
}

bool Board::check(pos leftBottom, pos rightTop) {
    for (size_t i = leftBottom.X; i <= rightTop.X; ++i) {
        for (size_t j = leftBottom.Y; j <= rightTop.Y; ++j) {
            if (mBoard[i][j]) {
                return true;
            }
        }
    }
    return false;
}
