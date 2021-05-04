#ifndef INC_8PUZZLE_TYPEDSTATE_H
#define INC_8PUZZLE_TYPEDSTATE_H

#include <string>
#include "MovementType.h"

template<typename IR>
class TypedState {
protected:
    // Current State (4*4 grid) stored in unsigned long long.
    IR state;
    // Position of 0 in 4*4 grid.
    int x0, y0;
    // Moves to get to this state. (e.g.ULUDR)
    std::string path;
    // Depth of path
    int depth;
public:
    // Copy constructor.
    TypedState(const TypedState &s);

    // Constructor from initial string and goal string. Assumes no moves. (Empty Path)
    explicit TypedState(std::string initialState);

    // Equality Comparison Operator. (checks state with NibbleState)
    bool operator==(const IR &rhs) const;

    // returns position of 0 in the string (used for vector arrays for visited list)
    int get0Pos() const;
    // TODO: Investigate whether bucketing the visited list will improve performance

    // Returns true if can move in direction
    bool canMoveDirection(MovementType movementType);
    // Returns State moved in direction
    TypedState moveDirection(MovementType movementType);

    // Returns state as string.
    IR getState() const;

    // Returns Path to get to state.
    std::string getPath();

    // Returns depth of path.
    int getDepth() const;
};


#endif //INC_8PUZZLE_TYPEDSTATE_H
