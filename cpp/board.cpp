#include "board.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <ostream>


Board::Board()
{
    this->pieceColorToMove = PieceColor::black;
    int row = 0, col = 0;
    for (int i = 0; i < 12; i++) {
        pieces.push_back(Piece(Position(row, col), PieceColor::white, PieceType::man));
        if (col == 6) {
            col = 1;
            row++;
        } else if (col == 7) {
            col = 0;
            row++;
        } else {
            col += 2;
        }
    }

    row = 5, col = 1;
    for (int i = 0; i < 12; i++) {
        pieces.push_back(Piece(Position(row, col), PieceColor::black, PieceType::man));
        if (col == 6) {
            col = 1;
            row++;
        } else if (col == 7) {
            col = 0;
            row++;
        } else {
            col += 2;
        }
    }
}

std::vector<Piece> Board::getPieces() const {
    return this->pieces;
}

Piece& Board::getPiece(int index) {
    if (!Board::isPieceIndexValid(index)) {
        throw "Invalid piece index!";
    }
    return pieces.at(index);
}

int Board::getPieceIndexByPosition(const Position &position) {
    for (int i = 0; i < pieces.size(); i++) {
        if (position == pieces.at(i).getPosition()) {
            return i;
        }
    }
    return -1;
}

std::optional<Piece> Board::getPiece(const Position &position) const {
    if (!Board::isPiecePositionValid(position)) {
        throw "Invalid piece position!";
    }
    std::optional<Piece> pieceToReturn {};
    for (auto piece : pieces) {
        if (piece.getPosition() == position) {
            pieceToReturn = piece;
            break;
        }
    }
    return pieceToReturn;
}

void Board::makeMove(Position &position, Move move, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position)) {
        throw "Invalid piece position!";
    }
    if (Board::canMakeMove(position, move)) {
        std::cout << "Lépés megléphető! :D";
        switch(move) {
        case Move::up_left:
            this->makeMoveUpLeft(position, pieceColor);
            lastMove = Move::up_left;
            break;
        case Move::up_right:
            this->makeMoveUpRight(position, pieceColor);
            lastMove = Move::up_right;
            break;
        case Move::down_left:
            this->makeMoveDownLeft(position, pieceColor);
            lastMove = Move::down_left;
            break;
        case Move::down_right:
            this->makeMoveDownRight(position, pieceColor);
            lastMove = Move::down_right;
            break;
        case Move::capture_up_left:
            this->makeMoveCaptureUpLeft(position, pieceColor);
            lastMove = Move::capture_up_left;
            break;
        case Move::capture_up_right:
            this->makeMoveCaptureUpRight(position, pieceColor);
            lastMove = Move::capture_up_right;
            break;
        case Move::capture_down_left:
            this->makeMoveCaptureDownLeft(position, pieceColor);
            lastMove = Move::capture_down_left;
            break;
        case Move::capture_down_right:
            this->makeMoveCaptureDownRight(position, pieceColor);
            lastMove = Move::capture_down_right;
            break;
        }
        if (pieceColorToMove == PieceColor::black &&
           (lastMove == Move::capture_down_left || lastMove == Move::capture_down_right ||
            lastMove == Move::capture_up_right || lastMove == Move::capture_up_left) &&
            !canCapture(pieceColorToMove)) {
            pieceColorToMove = PieceColor::white;
        } else if (pieceColorToMove == PieceColor::white &&
                  (lastMove == Move::capture_down_left || lastMove == Move::capture_down_right ||
                   lastMove == Move::capture_up_right || lastMove == Move::capture_up_left) &&
                   !canCapture(pieceColorToMove)) {
            pieceColorToMove = PieceColor::black;
        } else if (pieceColorToMove == PieceColor::black &&
                   (lastMove == Move::capture_down_left || lastMove == Move::capture_down_right ||
                    lastMove == Move::capture_up_right || lastMove == Move::capture_up_left) &&
                    canCapture(pieceColorToMove)) {
            // Not doing anything
        } else if (pieceColorToMove == PieceColor::white &&
                   (lastMove == Move::capture_down_left || lastMove == Move::capture_down_right ||
                    lastMove == Move::capture_up_right || lastMove == Move::capture_up_left) &&
                    canCapture(pieceColorToMove)) {
            // Not doing anything
        } else if (pieceColorToMove == PieceColor::white) {
            pieceColorToMove = PieceColor::black;
        } else if (pieceColorToMove == PieceColor::black) {
            pieceColorToMove = PieceColor::white;
        }
    }
}

void Board::makeMoveUpLeft(Position &position, PieceColor pieceColor) {
    if (shouldBecomeKing(position.getPositionAfterMove(Move::up_left, pieceColor), pieceColor)) {
        this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
    }
    position.setWithMove(Move::up_left, pieceColor);
}

void Board::makeMoveUpRight(Position &position, PieceColor pieceColor) {
    if (shouldBecomeKing(position.getPositionAfterMove(Move::up_right, pieceColor), pieceColor)) {
        this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
    }
    position.setWithMove(Move::up_right, pieceColor);
}

void Board::makeMoveDownLeft(Position &position, PieceColor pieceColor) {
    if (shouldBecomeKing(position.getPositionAfterMove(Move::down_left, pieceColor), pieceColor)) {
        this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
    }
    position.setWithMove(Move::down_left, pieceColor);
}

void Board::makeMoveDownRight(Position &position, PieceColor pieceColor) {
    if (shouldBecomeKing(position.getPositionAfterMove(Move::down_right, pieceColor), pieceColor)) {
        this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
    }
    position.setWithMove(Move::down_right, pieceColor);
}

void Board::makeMoveCaptureUpLeft(Position &position, PieceColor pieceColor) {
    for (int i = 0; i < this->pieces.size(); i++) {
        if (pieces[i].getPosition() == position.getPositionAfterMove(Move::up_left, pieceColor)) {
            if (shouldBecomeKing(position.getPositionAfterMove(Move::capture_up_left, pieceColor), pieceColor)) {
                this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
            }
            position.setWithMove(Move::capture_up_left, pieceColor);
            pieces.erase(pieces.begin() + i);
            break;
        }
    }
}

void Board::makeMoveCaptureUpRight(Position &position, PieceColor pieceColor) {
    for (int i = 0; i < this->pieces.size(); i++) {
        if (pieces[i].getPosition() == position.getPositionAfterMove(Move::up_right, pieceColor)) {
            if (shouldBecomeKing(position.getPositionAfterMove(Move::capture_up_right, pieceColor), pieceColor)) {
                this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
            }
            position.setWithMove(Move::capture_up_right, pieceColor);
            pieces.erase(pieces.begin() + i);
            break;
        }
    }
}

void Board::makeMoveCaptureDownLeft(Position &position, PieceColor pieceColor) {
    for (int i = 0; i < this->pieces.size(); i++) {
        if (pieces[i].getPosition() == position.getPositionAfterMove(Move::down_left, pieceColor)) {
            if (shouldBecomeKing(position.getPositionAfterMove(Move::capture_down_left, pieceColor), pieceColor)) {
                this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
            }
            position.setWithMove(Move::capture_down_left, pieceColor);
            pieces.erase(pieces.begin() + i);
            break;
        }
    }
}

void Board::makeMoveCaptureDownRight(Position &position, PieceColor pieceColor) {
    for (int i = 0; i < this->pieces.size(); i++) {
        if (pieces[i].getPosition() == position.getPositionAfterMove(Move::down_right, pieceColor)) {
            if (shouldBecomeKing(position.getPositionAfterMove(Move::capture_down_right, pieceColor), pieceColor)) {
                this->getPiece(this->getPieceIndexByPosition(position)).setPieceType(PieceType::king);
            }
            position.setWithMove(Move::capture_down_right, pieceColor);
            pieces.erase(pieces.begin() + i);
            break;
        }
    }
}

bool Board::canMakeMove(const Position &position, Move move) {
    PieceType pieceTypeToBeMoved{};
    PieceColor pieceColorToBeMoved{};
    for (auto piece : pieces) {
        if (piece.getPosition() == position) {
            pieceTypeToBeMoved = piece.getPieceType();
            pieceColorToBeMoved = piece.getPieceColor();
            break;
        }
    }
    if (pieceColorToBeMoved != this->pieceColorToMove) { // Ütésnél figyelj erre!
        return false;
    }
    bool canPieceMove;
    switch(move) {
        case Move::down_left:
            canPieceMove = Board::canMakeMoveDownLeft(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::down_right:
            canPieceMove = Board::canMakeMoveDownRight(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::up_left:
            canPieceMove = Board::canMakeMoveUpLeft(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::up_right:
            canPieceMove = Board::canMakeMoveUpRight(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::capture_down_left:
            canPieceMove = Board::canMakeMoveCaptureDownLeft(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::capture_down_right:
            canPieceMove = Board::canMakeMoveCaptureDownRight(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::capture_up_left:
            canPieceMove = Board::canMakeMoveCaptureUpLeft(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
        case Move::capture_up_right:
            canPieceMove = Board::canMakeMoveCaptureUpRight(position, pieceTypeToBeMoved, pieceColorToBeMoved);
            break;
    }
    return canPieceMove;
}

bool Board::canMakeMoveDownLeft(const Position &position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::down_left, pieceColor))) {
        return false;
    }
    if (canCapture(pieceColor)) {
        return false;
    }
    if(!Board::isSquareEmpty(position.getPositionAfterMove(Move::down_left, pieceColor))) {
        return false;
    }
    if (pieceColor == PieceColor::black && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveDownRight(const Position &position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::down_right, pieceColor))) {
        return false;
    }
    if (canCapture(pieceColor)) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::down_right, pieceColor))) {
        return false;
    }
    if (pieceColor == PieceColor::black && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveUpLeft(const Position &position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::up_left, pieceColor))) {
        return false;
    }
    if (canCapture(pieceColor)) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::up_left, pieceColor))) {
        return false;
    }
    if (pieceColor == PieceColor::white && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveUpRight(const Position &position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::up_right, pieceColor))) {
        return false;
    }
    if (canCapture(pieceColor)) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::up_right, pieceColor))) {
        return false;
    }
    if (pieceColor == PieceColor::white && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveCaptureDownLeft(const Position& position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::capture_down_left, pieceColor))) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::capture_down_left, pieceColor))) {
        return false;
    }
    if (Board::isSquareEmpty(position.getPositionAfterMove(Move::down_left, pieceColor))) {
        return false;
    }
    if(this->getPiece(position.getPositionAfterMove(Move::down_left, pieceColor)).value().getPieceColor() ==
       pieceColor) {
       return false;
    }
    if (pieceColor == PieceColor::black && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveCaptureDownRight(const Position& position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::capture_down_right, pieceColor))) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::capture_down_right, pieceColor))) {
        return false;
    }
    if (Board::isSquareEmpty(position.getPositionAfterMove(Move::down_right, pieceColor))) {
        return false;
    }
    if (this->getPiece(position.getPositionAfterMove(Move::down_right, pieceColor)).value().getPieceColor() ==
        pieceColor) {
        return false;
    }
    if (pieceColor == PieceColor::black && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveCaptureUpLeft(const Position& position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::capture_up_left, pieceColor))) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::capture_up_left, pieceColor))) {
        return false;
    }
    if (Board::isSquareEmpty(position.getPositionAfterMove(Move::up_left, pieceColor))) {
        return false;
    }
    if (this->getPiece(position.getPositionAfterMove(Move::up_left, pieceColor)).value().getPieceColor() ==
        pieceColor) {
        return false;
    }
    if (pieceColor == PieceColor::white && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canMakeMoveCaptureUpRight(const Position& position, PieceType pieceType, PieceColor pieceColor) {
    if (!Board::isPiecePositionValid(position.getPositionAfterMove(Move::capture_up_right, pieceColor))) {
        return false;
    }
    if (!Board::isSquareEmpty(position.getPositionAfterMove(Move::capture_up_right, pieceColor))) {
        return false;
    }
    if (Board::isSquareEmpty(position.getPositionAfterMove(Move::up_right, pieceColor))) {
        return false;
    }
    if (this->getPiece(position.getPositionAfterMove(Move::up_right, pieceColor)).value().getPieceColor() ==
        pieceColor) {
        return false;
    }
    if (pieceColor == PieceColor::white && pieceType != PieceType::king) {
        return false;
    }
    return true;
}

bool Board::canCapture(PieceColor pieceColor) {
    for (auto piece : pieces) {
        PieceColor pColor = piece.getPieceColor();
        if (pColor == pieceColor) {
            Position position = piece.getPosition();
            PieceType pieceType = piece.getPieceType();
            if (canMakeMoveCaptureUpRight(position, pieceType, pieceColor) ||
                canMakeMoveCaptureUpLeft(position, pieceType, pieceColor) ||
                canMakeMoveCaptureDownRight(position, pieceType, pieceColor) ||
                canMakeMoveCaptureDownLeft(position, pieceType, pieceColor)) {
                    return true;
            }
        }
    }
}

bool Board::isGameOver() {
    return this->whiteWins() || this->blackWins();
}

bool Board::hasRemainingPieces(PieceColor pieceColor) {
    for (auto piece : this->pieces) {
        if (piece.getPieceColor() == pieceColor) {
            return true;
        }
    }
    return false;
}

bool Board::hasPlayerLegalMoves(PieceColor pieceColor) {
    if (!Board::hasRemainingPieces(pieceColor)) {
        return false;
    }
    switch(pieceColor) {
        case PieceColor::white:
            return this->hasWhiteLegalMoves();
        case PieceColor::black:
            return this->hasBlackLegalMoves();
    }
}

bool Board::hasWhiteLegalMoves() {
    Move moves[] = {
        Move::up_left,
        Move::up_right,
        Move::down_left,
        Move::down_right,
        Move::capture_up_left,
        Move::capture_up_right,
        Move::capture_down_left,
        Move::capture_down_right
    };
    PieceColor original = this->pieceColorToMove;
    this->pieceColorToMove = PieceColor::white;
    for (auto piece : this->pieces) {
        if (piece.getPieceColor() == PieceColor::white) {
            for (auto move : moves) {
                if (canMakeMove(piece.getPosition(), move)) {
                    this->pieceColorToMove = original;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::hasBlackLegalMoves() {
    Move moves[] = {
        Move::up_left,
        Move::up_right,
        Move::down_left,
        Move::down_right,
        Move::capture_up_left,
        Move::capture_up_right,
        Move::capture_down_left,
        Move::capture_down_right
    };
    PieceColor original = this->pieceColorToMove;
    this->pieceColorToMove = PieceColor::black;
    for (auto piece : this->pieces) {
        if (piece.getPieceColor() == PieceColor::black) {
            for (auto move : moves) {
                if (canMakeMove(piece.getPosition(), move)) {
                    this->pieceColorToMove = original;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::whiteWins() {
    return !Board::hasRemainingPieces(PieceColor::black) || !Board::hasPlayerLegalMoves(PieceColor::black);
}

bool Board::blackWins() {
    return !Board::hasRemainingPieces(PieceColor::white) || !Board::hasPlayerLegalMoves(PieceColor::white);
}

bool Board::shouldBecomeKing(const Position& position, PieceColor pieceColor) {
    switch (pieceColor) {
        case PieceColor::black:
            return position.getRow() == 0 && this->getPiece(position)->getPieceType() == PieceType::man;
            break;
        case PieceColor::white:
            return position.getRow() == Board::board_size - 1 && this->getPiece(position)->getPieceType() == PieceType::man;
            break;
    }
}

bool Board::isSquareEmpty(const Position &position) const {
    if (!Board::getPiece(position).has_value()) {
        return true;
    }
    return false;
}

bool Board::isPiecePositionValid(const Position &position) const {
    return position.getRow() >= 0 && position.getRow() <= Board::board_size - 1
        && position.getCol() >= 0 && position.getCol() <= Board::board_size - 1;
}

bool Board::isPieceIndexValid(int index) const {
    return index >= 0 && index < this->pieces.size();
}
