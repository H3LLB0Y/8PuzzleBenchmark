#ifndef INC_8PUZZLE_NIBBLESTATE_H
#define INC_8PUZZLE_NIBBLESTATE_H

typedef unsigned long long NibbleState;

unsigned char characterToNibble(char character);

char nibbleToCharacter(unsigned char nibble);

NibbleState nibbleInPlace(NibbleState nibbleState, int x, int y);

#endif //INC_8PUZZLE_NIBBLESTATE_H
