#ifndef INC_8PUZZLE_MOVEMENTTYPE_H
#define INC_8PUZZLE_MOVEMENTTYPE_H

// TODO: Move to InternalRepresentation folder (or combine TypedState and InternalRepresentation)
enum class MovementType {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

std::ostream &operator<<(std::ostream &stream, MovementType movementType);

#endif //INC_8PUZZLE_MOVEMENTTYPE_H
