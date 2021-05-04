#ifndef INC_8PUZZLE_INTERNALREPRESENTATION_H
#define INC_8PUZZLE_INTERNALREPRESENTATION_H

#include <string>

#include "StringState/StringState.h"
#include "NibbleState/NibbleState.h"
#include "IntegerState/IntegerState.h"

#include "../TypedState/MovementType.h"

template<typename IR>
extern std::string internalRepresentationName();

template<typename IR>
extern IR stringToIR(const std::string &state);

template<typename IR>
extern std::string stringFromIR(IR state);

template<typename IR>
extern IR adjust(IR state, int x, int y, MovementType movementType);

#endif //INC_8PUZZLE_INTERNALREPRESENTATION_H
