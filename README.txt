8 Puzzle Benchmarking Program

3 Internal Representations (Types that the TypedState class uses for representing the board state):
- IntegerState:
State is represented by a single 32-bit integer.
Conversion between string representation and IntegerState is done using "stoi" and "to_string" functions.
Internally numbers are moved around by extracting the value, and subtracting and adding multiplied by pow(10, [# place]).
Representing the "state" as a single integer means we can do 1:1 comparisons between them more efficiently with integer comparison.
- NibbleState:
State is represented by a single 64-bit unsigned integer.
Conversion from string representation to NibbleState is done by shifting the value (adjusted from ASCII to 0-9) to it's place and bitwise-or'ing.
Conversion to string representation from NibbleState is done by extracting the value in order (and adjusting back to ASCII) and appending to a string (pre-reserved).
As with IntegerState, representing the "state" as a single value means we can more efficiently compare the state values.
Performance comparisons between NibbleState and IntegerState don't show a huge improvement (like either compared with StringState) but it is perfect size for extending 8-Puzzle to 15-Puzzle so can be extended to that.
- StringState:
Baseline representation. State is represented by a c++ string.
Adjustment is done by extracting character from place and replacing with '0' and moving character to old '0' place.
Comparison between states is done via string comparison, so could potentially involve 1-8 comparisons (depending on how exact they are). This was the catalyst behind developing the IntegerState equivalent back in university.


Files
- InternalRepresentation/
	- IntegerState/
		- IntegerState.cpp
		- IntegerState.h
	- NibbleState/
		- NibbleState.cpp
		- NibbleState.h
	- StringState/
		- StringState.cpp
		- StringState.h
- SearchAlgorithms/
	- AStarSearch/
		- AStarSearch.cpp
		- AStarSearch.h
	- BreadthFirstSearch/
		- BreadthFirstSearch.cpp
		- BreadthFirstSearch.h
	- DepthFirstSearch/
		- DepthFirstSearch.cpp
		- DepthFirstSearch.h
	- ProgressiveDeepeningSearch/
		- ProgressiveDeepeningSearch.cpp
		- ProgressiveDeepeningSearch.h
- TypedState/
	- TypedState.cpp
	- TypedState.h
- CMakeLists.txt - CMake file to build solution
- main.cpp - Entry point for solution. Runs NUM_RUNS tests on 5 initial states [for each state (3 different internal representations (IR) [for each IR (4 different algorithms)]]
- results.csv - Latest test run results with NUM_RUNS at 100.


The A Star implementation is not quite as explained in the lectures.
It does retrieve the shortest FCost node, but does not remove longer paths to states already in Q.
The time reduction is much greater than the duplicate states cut from the Q.

My State implementation uses integers rather than strings, which gives much faster times than string.
Comparisons between 2 integers will be much faster than string-string comparisons.
The integer is the 9 values of the squares as they would be in the string. So square 0 is far left in int (e.g 500000000), and square 8 is 0-8 value of the square (e.g 5).

By using integer manipulation it is easy to move numbers around inside the int, and probably faster than string character movement.

y0 and x0 are the position of the 0 in the 8 square.

int num=(int)(retval->state/(pow(10.0,(8-((y0-1)*3+x0)))))%10;	// retrieve number from position
retval->state-=num*pow(10.0,(8-((y0-1)*3+x0)));						// move number to 0 position
retval->state+=num*pow(10.0,(8-(y0*3+x0)));							// move 0
_______________________________________________________________________________

State Class (A more simplified version of the Puzzle Class)

class State {
protected:
	int state;	// Current State (3*3 grid) stored in int.
	string path;	// Moves to get to this state. (e.g.ULUDR)
	int x0,y0;		// Position of 0 in 3*3 grid.
	int depth;		// Depth of path
public:
	State(const State &s);	// Copy constructor.
	State(const string state); // Constructor from initial string and goal string. Assumes no moves. (Empty Path)
	bool operator==(const int &rhs); // Equality Comparison Operator. (checks state with int)
	int get0Pos();			// returns position of 0 in the string
	State *moveUp();		// Returns Moved Up State or nullptr if cannot move up.
	State *moveRight();	// Returns Moved Right State or nullptr if cannot move up.
	State *moveDown();	// Returns Moved Down State or nullptr if cannot move up.
	State *moveLeft();	// Returns Moved Left State or nullptr if cannot move up.
	string toString();	// Returns state as string.
	int getState();		// returns state in int form
	void setStateString(string state);	// Set State string to state parameter.
	void setStateInt(int state);	// Set State string to state parameter.
	string getPath();					// Returns Path to get to state.
	int getDepth();					// Returns depth of path.
	void appendToPath(char c);		// Appends character c onto path string.
};
_______________________________________________________________________________

Heuristic State Class (For A Star Search)

class HeuristicState : public State {
private:
	int hValue;		// Heuristic Value to get to goalState. (calculated in calcHValue function) 
public:
	HeuristicState(const string state,const string goalstate); // Constructor from initial string and goal string. Assumes no moves. (Empty Path)
	bool operator==(const int &rhs); // Equality Comparison Operator. (checks state with int)
	void calcHValue(const string goalstate);	// Calculates Heuristic Value from current state and goal state.
	int getH();				// get Heuristic Value. (Pre-calculated in calcHValue function)
};
_______________________________________________________________________________

Depth First Search:

Create State from both initial and goal state strings passed in function call.
Initialise Visited List to empty. (Using a Set for speed. Additions are placed in the correct order which makes searching time logarithmic rather than linear.)
Initialise Queue to empty. (Using a Stack as you only need to be able to access the top.)
Put current state on the Queue and add to the Visited List.

Loop starts here {
	Take element from front of Queue. If it is empty return empty path.
	(Check depth of path, if its greater than max depth then backtrack.)
	Find descendents of current state.
	Check Up,Right,Down,Left and extract.
	Put them on Visited List.
	(Increment number of state expansions.)
	Put descendents in front of queue, left,down,right,up. So Up is on the outside of the queue and first to be taken off.
}
_______________________________________________________________________________

Breadth First Search:

Create State from both initial and goal state strings passed in function call.
Initialise Visited List to empty. (Using a Set for speed. Additions are placed in the correct order which makes searching time logarithmic rather than linear.)
Initialise Queue to empty. (Using a Queue as you only need to be able to access the front, and put on the end.)
Put current state on the Queue and add to the Visited List.

Loop starts here {
	Take element from front of Queue. If it is empty return empty path.
	(Check depth of path, if its greater than max depth then backtrack.)
	Find descendents of current state.
	Check Up,Right,Down,Left and extract.
	Put them on Visited List.
	(Increment number of state expansions.)
	Put descendents on end of queue, up,right,down,left. So Up is on the outside of the queue and first to be taken off.
}
_______________________________________________________________________________

Progressive Deepening Search:

Depth d = 1.
Loop through until result is found or max depth is reached {
	Call Depth First Search with depth d.
	Increment Depth d.
}
_______________________________________________________________________________

A Star Search:

Create State from both initial and goal state strings passed in function call.
Initialise Expanded List to empty. (Using a Set for speed. Additions are placed in the correct order which makes searching time logarithmic rather than linear.)
Initialise Queue to empty. (Using a multimap, using an int key (the total FCost for the state) and a pointer to the HeuristicState as the value, because additions are placed in the correct order retrieving the first element will always give the lowest FCost, or the first of that cost to be added.)
Put current state on the Queue.

Loop starts here {
	If Queue is empty return empty path.
	Take element from front of Queue. (will be shortest FCost.)
	(Check depth of path, if its greater than max depth then backtrack.)
	(Check if state is already in Expanded List.)
	If not then put them on Expanded List.
	(Increment number of state expansions.)
	Check for goalmatch.
	Find descendents of current state.
	Check Up,Right,Down,Left and extract.
	If descendents arent on expanded list, insert into Queue.
}
