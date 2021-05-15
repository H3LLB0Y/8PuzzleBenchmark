#include "NibbleState.h"

#include "../InternalRepresentation.h"

#include <stdexcept>
#include <string>

unsigned char characterToNibble(char character) {
    switch (character) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return character - '0';
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return character - 'A' + 0xA;
        default:
            throw std::invalid_argument("Character must be a HEX character!");
    }
}

char nibbleToCharacter(unsigned char nibble) {
    if (nibble < 0xA) {
        return '0' + nibble;
    } else {
        return 'A' - 0xA + nibble;
    }
}

NibbleState nibbleInPlace(NibbleState nibbleState, int x, int y) {
    return nibbleState & ((NibbleState) 0xF << ((y * 4 + x) * 4));
}

template<>
std::string internalRepresentationName<NibbleState>() {
    return "NibbleState";
}

template<>
NibbleState stringToIR<NibbleState>(const std::string &state) {
    NibbleState nibbleState = 0ULL;
    switch (state.length()) {
        case 9:
            for (int y = 0; y < 3; ++y) {
                for (int x = 0; x < 3; ++x) {
                    // TODO: Utility functions! for 2D->1D
                    NibbleState character = characterToNibble(state[y * 3 + x]);
                    nibbleState |= character << ((y * 4 + x) * 4);
                }
            }
            break;
        case 16:
            for (int y = 0; y < 4; ++y) {
                for (int x = 0; x < 4; ++x) {
                    NibbleState character = characterToNibble(state[y * 4 + x]);
                    nibbleState |= character << ((y * 4 + x) * 4);
                }
            }
            break;
        default:
            throw std::invalid_argument("State must be either 9 or 16 characters long!");
    }
    return nibbleState;
}

template<>
std::string stringFromIR<NibbleState>(NibbleState state) {
    std::string string;
    string.reserve(16);
    // TODO: Do for 16
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            int index = (y * 4 + x) * 4;
            char character = nibbleToCharacter((state >> index) & 0xF);
            string += character;
        }
    }
    return string;
}

template<>
NibbleState adjust<NibbleState>(NibbleState state, int x, int y, MovementType movementType) {
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
    NibbleState inPlace = nibbleInPlace(state, x, y);
    state ^= inPlace;
    switch (movementType) {
        case MovementType::UP:
            inPlace <<= 4 * 4;
            break;
        case MovementType::RIGHT:
            inPlace >>= 1 * 4;
            break;
        case MovementType::DOWN:
            inPlace >>= 4 * 4;
            break;
        case MovementType::LEFT:
            inPlace <<= 1 * 4;
            break;
    }
    state |= inPlace;
    return state;
}
