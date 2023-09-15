#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include "pieceColor.h"
#include "pieceType.h"


class Piece
{
public:

    Piece(Position piecePosition, PieceColor color, PieceType type);

    Position& getPosition();

    PieceColor getPieceColor() const;

    PieceType getPieceType() const;

    void setPieceType(PieceType newPieceType);

    bool operator==(Piece &other) const;

    bool operator!=(Piece &other) const;

private:

    Position position;
    PieceColor pieceColor;
    PieceType pieceType;

};

#endif // PIECE_H
