#include <stdexcept>
#include "TypedState.h"
#include "../InternalRepresentations/InternalRepresentation.h"

template<typename IR>
TypedState<IR>::TypedState(const std::string initialState): state(stringToIR<IR>(initialState)) {
    // TODO: Optimize the find '0' (Maybe InternalRepresentation specific?)
    // TODO: sqrt on initialState.length to get modulus/division RH
    // TODO: Also assert on length (or pass IR in instead of string?)
    switch (initialState.length()) {
        case 9:
            for (int i = 0; i < 9; ++i) {
                if (initialState[i] == '0') {
                    x0 = i % 3;
                    y0 = i / 3;
                    break;
                }
            }
            break;
        case 16:
            for (int i = 0; i < 16; ++i) {
                if (initialState[i] == '0') {
                    x0 = i % 4;
                    y0 = i / 4;
                    break;
                }
            }
            break;
    }
    path = "";
    depth = 0;
}

template<typename IR>
bool TypedState<IR>::operator==(const IR &rhs) const {
    if (state != rhs) {
        return false;
    }
    return true;
}

template<typename IR>
bool TypedState<IR>::canMoveDirection(MovementType movementType) {
    switch (movementType) {
        case MovementType::UP:
            return y0 != 0;
        case MovementType::RIGHT:
            return x0 != 2;
        case MovementType::DOWN:
            return y0 != 2;
        case MovementType::LEFT:
            return x0 != 0;
        default:
            // TODO: Move to after switch
            throw std::invalid_argument("Argument must be MovementType");
    }
}

char letterForDirection(MovementType movementType) {
    switch (movementType) {
        case MovementType::UP:
            return 'U';
        case MovementType::RIGHT:
            return 'R';
        case MovementType::DOWN:
            return 'D';
        case MovementType::LEFT:
            return 'L';
        default:
            // TODO: Move to after switch
            throw std::invalid_argument("Argument must be MovementType");
    }
}

template<typename IR>
TypedState<IR> TypedState<IR>::moveDirection(MovementType movementType) {
    auto returnValue = TypedState(*this);

    returnValue.state = adjust<IR>(state, x0, y0, movementType);

    switch (movementType) {
        case MovementType::UP:
            --returnValue.y0;
            break;
        case MovementType::RIGHT:
            ++returnValue.x0;
            break;
        case MovementType::DOWN:
            ++returnValue.y0;
            break;
        case MovementType::LEFT:
            --returnValue.x0;
            break;
    }
    returnValue.path.push_back(letterForDirection(movementType));
    ++returnValue.depth;
    return returnValue;
}

template<typename IR>
IR TypedState<IR>::getState() const {
    return state;
}

template<typename IR>
std::string TypedState<IR>::getPath() {
    return path;
}

template<typename IR>
int TypedState<IR>::getDepth() const {
    return depth;
}

template<typename IR>
int TypedState<IR>::get0Pos() const {
    return y0 * 3 + x0;
}

template class TypedState<StringState>;

template class TypedState<IntegerState>;

template class TypedState<NibbleState>;
