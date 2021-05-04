#include <set>
#include <iostream>
#include "AStarSearch.h"

template<typename IR>
int calculateHeuristicValue(IR state, IR goalState) {
    // TODO: Maybe optimize this function somewhat (Representation specific?)
    int value = 0;
    std::string tempState = stringFromIR<IR>(state);
    std::string tempGoalState = stringFromIR<IR>(goalState);
    // loop through all numbers to calculate their manhatten distance
    for (int n = 0 + 48; n < 9 + 48; ++n) {
        int x, y;
        int x1, y1, x2, y2;

        for (y = 0; y < 3; ++y) {
            for (x = 0; x < 3; ++x) {
                if (tempState[y * 3 + x] == n) {
                    x1 = x;
                    y1 = y;
                    break;
                }
            }
        }
        for (y = 0; y < 3; ++y) {
            for (x = 0; x < 3; ++x) {
                if (tempGoalState[y * 3 + x] == n) {
                    x2 = x;
                    y2 = y;
                    break;
                }
            }
        }
        // and add together
        value += (abs(x1 - x2) + abs(y1 - y2));
    }
    return value;
}

template<typename IR>
void AStarSearch<IR>::addToQueue(std::multimap<int, TypedState<IR>> &queue, TypedState<IR> state) {
    int heuristicValue = calculateHeuristicValue(state.getState(), mGoalState);
    // add node to queue (will be placed according to F cost (heuristic and depth)
    auto pair = std::pair<int, TypedState<IR>>(
            state.getDepth() + heuristicValue,
            state
    );
    queue.insert(pair);
}

template<typename IR>
bool AStarSearch<IR>::queueEmpty(std::multimap<int, TypedState<IR>> &queue) {
    return queue.empty();
}

template<typename IR>
int AStarSearch<IR>::getQueueSize(std::multimap<int, TypedState<IR>> &queue) {
    return queue.size();
}

template<typename IR>
std::list<MovementType> AStarSearch<IR>::getSearchDirectionOrder() {
    return {
            MovementType::UP,
            MovementType::RIGHT,
            MovementType::DOWN,
            MovementType::LEFT
    };
}

template<typename IR>
TypedState<IR> AStarSearch<IR>::getNext(std::multimap<int, TypedState<IR>> &queue) {
    auto it = queue.begin();
    auto next = it->second;
    queue.erase(it);
    return next;
}

template<typename IR>
SearchResults AStarSearch<IR>::runSearch(
        const std::string &initialState,
        const std::string &goalState,
        int maxDepth
) {
    int numberOfStateExpansions = 0;
    int maxQueueLength = 0;

    IR internalGoalState = stringToIR<IR>(goalState);
    mGoalState = internalGoalState;
    TypedState<IR> currentState = TypedState<IR>(initialState);

    auto queue = std::multimap<int, TypedState<IR>>();
    addToQueue(queue, currentState);

    auto expanded = std::set<IR>();

    while (!queueEmpty(queue)) {
        int queueSize = getQueueSize(queue);
        if (queueSize > maxQueueLength) {
            maxQueueLength = queueSize;
        }

        currentState = getNext(queue);

        ++numberOfStateExpansions;

        if (currentState == internalGoalState) {
            return makeSearchResults(
                    numberOfStateExpansions,
                    maxQueueLength,
                    currentState.getPath()
            );
        }

        auto state = currentState.getState();
        if (expanded.find(state) == expanded.end()) {
            expanded.insert(state);
        } else {
            continue;
        }

        if (currentState.getDepth() >= maxDepth) {
            continue;
        }

        for (auto direction : getSearchDirectionOrder()) {
            // TODO: Don't do left if last was right, etc
            if (currentState.canMoveDirection(direction)) {
                auto moved = currentState.moveDirection(direction);

                // if not in the expanded list
                IR movedState = moved.getState();
                if (expanded.find(movedState) == expanded.end()) {
                    addToQueue(queue, moved);
                }
            }
        }
    }

    // Q is empty return empty path, No solution found! :'(
    return makeSearchResults(
            numberOfStateExpansions,
            maxQueueLength,
            ""
    );
}

template
class AStarSearch<StringState>;

template
class AStarSearch<IntegerState>;

template
class AStarSearch<NibbleState>;

template<>
std::string searchAlgorithmTypeName<AStarSearch<StringState>>() {
    return "AStarSearch";
}

template<>
std::string searchAlgorithmTypeName<AStarSearch<IntegerState>>() {
    return "AStarSearch";
}

template<>
std::string searchAlgorithmTypeName<AStarSearch<NibbleState>>() {
    return "AStarSearch";
}
