#include "IntegerState.h"

#include <cmath>
#include <stdexcept>
#include <string>

#include "../InternalRepresentation.h"

template<>
std::string internalRepresentationName<IntegerState>() {
    return "IntegerState";
}

template<>
IntegerState stringToIR<IntegerState>(const std::string &state) {
    // TODO: Can probably optimize this some if it's base 10 always
    // TODO: Exception for bad string?
    return std::stoi(state);
}

template<>
std::string stringFromIR<IntegerState>(IntegerState state) {
    // TODO: Can probably optimize this some if it's base 10 always
    std::string asString = std::to_string(state);
    if (asString.length() == 8) {
        asString = "0" + asString;
    }
    return asString;
}

template<>
IntegerState adjust<IntegerState>(IntegerState state, int x, int y, MovementType movementType) {
    // TODO: Optimize this, so x/y is a single variable
    int powInsert = (8 - (y * 3 + x));
    switch (movementType) {
        case MovementType::UP:
            --y;
            break;
        case MovementType::RIGHT:
            ++x;
            break;
        case MovementType::DOWN:
            ++y;
            break;
        case MovementType::LEFT:
            --x;
            break;
    }
    int powExtract = (8 - (y * 3 + x));
    int num = (int) (state / (pow(10.0, powExtract))) % 10;
    state -= num * pow(10.0, powExtract);
    state += num * pow(10.0, powInsert);
    return state;
}
