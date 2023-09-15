#include "piece.h"

Piece::Piece(Position piecePosition, PieceColor color, PieceType type)
    : position(piecePosition), pieceColor(color), pieceType(type) {}

Position& Piece::getPosition() {
    return position;
}

PieceColor Piece::getPieceColor() const {
    return this->pieceColor;
}

PieceType Piece::getPieceType() const {
    return this->pieceType;
}

void Piece::setPieceType(PieceType newPieceType) {
    this->pieceType = newPieceType;
}

bool Piece::operator==(Piece &other) const {
    return this->position == other.getPosition() &&
           this->pieceColor == other.getPieceColor() &&
           this->pieceType == other.getPieceType();
}

bool Piece::operator!=(Piece &other) const {
    return !(*this == other);
}
