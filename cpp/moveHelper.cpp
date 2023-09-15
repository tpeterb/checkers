#include "moveHelper.h"
#include "move.h"
#include "position.h"
#include <optional>

std::optional<Move> MoveHelper::getMoveFromCoordinateChanges(Position startPosition, Position endPosition, PieceColor pieceColor) {

    int rowChange = endPosition.getRow() - startPosition.getRow();
    int colChange = endPosition.getCol() - startPosition.getCol();

    std::optional<Move> moveToReturn {};

    if (rowChange == -1 && colChange == -1) {
        return moveToReturn.emplace(Move::up_left);
    } if (rowChange == -1 && colChange == 1) {
        return moveToReturn.emplace(Move::up_right);
    } if (rowChange == 1 && colChange == -1) {
        return moveToReturn.emplace(Move::down_left);
    } if (rowChange == 1 && colChange == 1) {
        return moveToReturn.emplace(Move::down_right);
    } if (rowChange == -2 && colChange == -2) {
        return moveToReturn.emplace(Move::capture_up_left);
    } if (rowChange == -2 && colChange == 2) {
        return moveToReturn.emplace(Move::capture_up_right);
    } if (rowChange == 2 && colChange == -2) {
        return moveToReturn.emplace(Move::capture_down_left);
    } if (rowChange == 2 && colChange == 2) {
        return moveToReturn.emplace(Move::capture_down_right);
    }
    return moveToReturn;
}

