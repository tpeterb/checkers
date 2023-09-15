#include "position.h"
#include "pieceColor.h"

Position::Position() {

}

Position::Position(int rowNum, int colNum) : row(rowNum), col(colNum) {}

int Position::getRow() const {
    return this->row;
}

void Position::setRow(int rowNum) {
    this->row = rowNum;
}

int Position::getCol() const {
    return this->col;
}

void Position::setCol(int colNum) {
    this->col = colNum;
}

void Position::setWithMove(Move move, PieceColor pieceColor) {
    switch(move) {
        case Move::up_left:
            row--;
            col--;
            break;
        case Move::up_right:
            row--;
            col++;
            break;
        case Move::down_left:
            row++;
            col--;
            break;
        case Move::down_right:
            row++;
            col++;
            break;
        case Move::capture_up_left:
            row -= 2;
            col -= 2;
            break;
        case Move::capture_up_right:
            row -= 2;
            col += 2;
            break;
        case Move::capture_down_left:
            row += 2;
            col -= 2;
            break;
        case Move::capture_down_right:
            row += 2;
            col += 2;
            break;
    }
}

Position Position::getPositionAfterMove(Move move, PieceColor pieceColor) const {
    switch(move) {
        case Move::up_left:
            return Position(row - 1, col - 1);
        case Move::up_right:
            return Position(row - 1, col + 1);
        case Move::down_left:
            return Position(row + 1, col - 1);
        case Move::down_right:
            return Position(row + 1, col + 1);
        case Move::capture_up_left:
            return Position(row - 2, col - 2);
        case Move::capture_up_right:
            return Position(row - 2, col + 2);
        case Move::capture_down_left:
            return Position(row + 2, col - 2);
        case Move::capture_down_right:
            return Position(row + 2, col + 2);
    }
}

Position Position::of(int row, int col) {
    return Position(row, col);
}

bool Position::operator==(const Position &position) const {
    return this->row == position.getRow() && this->col == position.getCol();
}

bool Position::operator!=(const Position &position) const {
    return !(*this == position);
}
