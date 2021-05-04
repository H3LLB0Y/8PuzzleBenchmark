#include "StringState.h"

template<>
std::string internalRepresentationName<StringState>() {
    return "StringState";
}

template<>
StringState stringToIR<StringState>(const std::string &state) {
    return state;
}

template<>
std::string stringFromIR<StringState>(StringState state) {
    return state;
}

template<>
StringState adjust<StringState>(StringState state, int x, int y, MovementType movementType) {
    int from;
    int to = y * 3 + x;
    switch (movementType) {
        case MovementType::UP:
            from = (y - 1) * 3 + x;
            break;
        case MovementType::RIGHT:
            from = y * 3 + x + 1;
            break;
        case MovementType::DOWN:
            from = (y + 1) * 3 + x;
            break;
        case MovementType::LEFT:
            from = y * 3 + x - 1;
            break;
    }
    char oldCharacter = state[from];
    StringState newState = state;
    newState[from] = '0';
    newState[to] = oldCharacter;
    return newState;
}
