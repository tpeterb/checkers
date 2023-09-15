#ifndef MOVEHELPER_H
#define MOVEHELPER_H

#include "move.h"
#include "position.h"
#include <optional>

class MoveHelper {

public:

    static std::optional<Move> getMoveFromCoordinateChanges(Position startPosition, Position endPosition, PieceColor pieceColor);

protected:

    MoveHelper();

};

#endif // MOVEHELPER_H
