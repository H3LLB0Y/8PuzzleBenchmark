#include <ostream>
#include "MovementType.h"

std::ostream &operator<<(std::ostream &stream, MovementType movementType) {
    std::string enumString;
    switch (movementType) {
        case MovementType::UP:
            enumString = "UP";
            break;
        case MovementType::RIGHT:
            enumString = "RIGHT";
            break;
        case MovementType::DOWN:
            enumString = "DOWN";
            break;
        case MovementType::LEFT:
            enumString = "LEFT";
            break;
    }
    return stream << enumString;
}
