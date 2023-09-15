#ifndef POSITION_H
#define POSITION_H

#include "move.h"
#include "pieceColor.h"


class Position
{
public:

    Position();

    Position(int row, int col);

    int getRow() const;

    void setRow(int rowNum);

    int getCol() const;

    void setCol(int colNum);

    void setWithMove(Move move, PieceColor pieceColor);

    Position getPositionAfterMove(Move move, PieceColor pieceColor) const;

    static Position of(int row, int col);

    bool operator==(const Position &position) const;

    bool operator!=(const Position &position) const;

private:

    int row;
    int col;
};

#endif // POSITION_H
