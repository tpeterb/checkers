#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <vector>
#include <optional>


class Board
{
public:

    static const int board_size = 8;

    Board();

    std::vector<Piece> getPieces() const;

    Piece& getPiece(int index);

    std::optional<Piece> getPiece(const Position &position) const;

    int getPieceIndexByPosition(const Position &position);

    void makeMove(Position &position, Move move, PieceColor pieceColor);

    bool isGameOver();

    void makeMoveUpLeft(Position& position, PieceColor pieceColor);

    void makeMoveUpRight(Position& position, PieceColor pieceColor);

    void makeMoveDownLeft(Position& position, PieceColor pieceColor);

    void makeMoveDownRight(Position& position, PieceColor pieceColor);

    void makeMoveCaptureUpLeft(Position& position, PieceColor pieceColor);

    void makeMoveCaptureUpRight(Position& position, PieceColor pieceColor);

    void makeMoveCaptureDownLeft(Position& position, PieceColor pieceColor);

    void makeMoveCaptureDownRight(Position& position, PieceColor pieceColor);

    bool canMakeMove(const Position& position, Move move);

    bool canMakeMoveDownLeft(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveDownRight(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveUpLeft(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveUpRight(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveCaptureDownLeft(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveCaptureDownRight(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveCaptureUpLeft(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canMakeMoveCaptureUpRight(const Position& position, PieceType pieceType, PieceColor pieceColor);

    bool canCapture(PieceColor pieceColor);

    bool hasRemainingPieces(PieceColor pieceColor); //pipa

    bool hasPlayerLegalMoves(PieceColor pieceColor); //pipa

    bool hasWhiteLegalMoves(); //pipa

    bool hasBlackLegalMoves(); //pipa

    bool whiteWins();

    bool blackWins();

    bool isSquareEmpty(const Position& position) const; //pipa

    bool isPieceIndexValid(int index) const; //pipa

    bool isPiecePositionValid(const Position& position) const; //pipa

    bool shouldBecomeKing(const Position& position, PieceColor pieceColor);

private:

    std::vector<Piece> pieces;

    PieceColor pieceColorToMove;

    Move lastMove;
};

#endif // BOARD_H
