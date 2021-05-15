8 Puzzle Benchmarking Program

4 Search Algorithms:
- SearchAlgorithm:
Base class which has common behaviour of the searches. Templated class to handle the 3 different Internal Representations.
- DepthFirstSearch:
Uses STL Stack as it's internal 'queue' due to the Depth First algorithm workings. Needing to only access the one end of the 'queue' made the Stack the logical choice. Searches Left,Down,Right,Up.
- ProgressiveDeepeningSearch:
Uses DepthFirstSearch internally. Iterating from depth of 1 through to maxDepth (stopping if it finds a solution along the way) and calling DepthFirstSearch passing it's current value of depth as maxDepth.
- BreadthFirstSearch:
Uses STL Queue as it's internal 'queue' due to the Bread First algorithm workings. Needing to push to one end and pull off the other made the Queue the logical choice. Searches Up,Right,Down,Left: opposite order to DepthFirstSearch so they both search in the same order. (because BreadthFirst is pulling off the opposite end of the queue)
- AStarSearch:
Uses the Manhatten distance + depth as it's F Cost to run the A Star algorithm search.
Overrides processCurrentState so it can check for success when it pulls the state off the 'queue' rather than when it reaches the state (as it is in the other algorithms).

Typed State class:
Holds:
- state is the current board state
- x0 and y0 are the current 0 position on the board (empty square)
- path is the steps taken to reach this current state
- depth is how many steps (path.length)
Moving to another state creates a new instance of State class with updated values respective of the move.

3 Internal Representations (Types that the TypedState class uses for representing the board state):
- StringState:
Baseline representation. State is represented by a c++ string.
Adjustment is done by extracting character from place and replacing with '0' and moving character to old '0' place.
Comparison between states is done via string comparison, so could potentially involve 1-8 comparisons (depending on how exact they are). This was the catalyst behind developing the IntegerState equivalent back in university.
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
