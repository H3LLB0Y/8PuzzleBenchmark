#ifndef INC_8PUZZLE_INTERNALREPRESENTATION_H
#define INC_8PUZZLE_INTERNALREPRESENTATION_H

#include "StringState/StringState.h"
#include "IntegerState/IntegerState.h"
#include "NibbleState/NibbleState.h"

#include "../TypedState/MovementType.h"

// TODO: Consider and alternative name for InternalRepresentation
// TODO: Something shorter would be nice xD
template<typename IR>
extern std::string internalRepresentationName();

template<typename IR>
extern IR stringToIR(const std::string &state);

template<typename IR>
extern std::string stringFromIR(IR state);

// TODO: Name this better so it's self-explanatory what it does (or document it!)
template<typename IR>
extern IR adjust(IR state, int x, int y, MovementType movementType);

#endif //INC_8PUZZLE_INTERNALREPRESENTATION_H
