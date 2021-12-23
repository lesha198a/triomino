#ifndef TRIOMINO_BOARD_H
#define TRIOMINO_BOARD_H


#include <iostream>

class Board {
public:
    Board(size_t n);

    Board(const Board &board);

    ~Board();


    bool setPoint(size_t x, size_t y);

    void run();

    friend std::ostream &operator<<(std::ostream &stream, const Board &board);


    static Board createBoard();

private:
    struct pos {
        pos(size_t x, size_t y) : X(x), Y(y) {}

        size_t X = -1;
        size_t Y = -1;
    };

    void place(pos leftBottom, pos rightTop);
    bool check(pos leftBottom, pos rightTop);

    bool **mBoard = nullptr;
    size_t mLength = 0;
};


#endif//TRIOMINO_BOARD_H
