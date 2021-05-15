#include <set>
#include <iostream>
#include "AStarSearch.h"

template<typename IR>
std::string AStarSearch<IR>::searchAlgorithmTypeName() {
    return "AStarSearch";
}

template<typename IR>
int calculateHeuristicValue(IR state, IR goalState) {
    // TODO: Optimize this function somewhat (InternalRepresentation specific?)
    // TODO: For Nibble, something like xor the 2 states together
    // Then iterate looking for non-zero, extract value from one side, look for in other
    // Calculate manhatten based on that, continue down until all found
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
void AStarSearch<IR>::addToQueue(
        std::multimap<int, TypedState<IR>> &queue,
        TypedState<IR> state,
        std::set<IR> &alreadyChecked
) {
    int heuristicValue = calculateHeuristicValue(state.getState(), mGoalState);
    // add node to queue (will be placed according to F cost (heuristic and depth)
    auto pair = std::pair<int, TypedState<IR>>(
            state.getDepth() + heuristicValue,
            state
    );
    queue.insert(pair);
}

template<typename IR>
void
AStarSearch<IR>::addToQueueIfNotAlreadyChecked(
        std::multimap<int, TypedState<IR>> &queue,
        TypedState<IR> typedState,
        std::set<IR> &alreadyChecked
) {
    auto state = typedState.getState();
    if (alreadyChecked.find(state) == alreadyChecked.end()) {
        addToQueue(queue, typedState, alreadyChecked);
    }
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
std::optional<std::string>
AStarSearch<IR>::processCurrentState(
        std::multimap<int, TypedState<IR>> &queue,
        TypedState<IR> currentState,
        IR internalGoalState,
        std::set<IR> &alreadyChecked
) {
    // Check if currentState is goalState
    if (currentState == internalGoalState) {
        return currentState.getPath();
    }
    auto state = currentState.getState();
    if (alreadyChecked.find(state) == alreadyChecked.end()) {
        // TODO: Insert and check pair::second instead of checking find==end?
        // https://stackoverflow.com/questions/97050/stdmap-insert-or-stdmap-find
        alreadyChecked.insert(state);
    } else {
        return std::nullopt;
    }

    for (auto direction : getSearchDirectionOrder()) {
        // TODO: Don't do left if last was right, etc
        if (currentState.canMoveDirection(direction)) {
            auto moved = currentState.moveDirection(direction);
            addToQueueIfNotAlreadyChecked(
                    queue,
                    moved,
                    alreadyChecked
            );
        }
    }

    return std::nullopt;
}

template<typename IR>
SearchResults AStarSearch<IR>::runSearch(
        const std::string &initialState,
        const std::string &goalState,
        int maxDepth
) {
    mGoalState = stringToIR<IR>(goalState);
    return SearchAlgorithm<IR, std::multimap<int, TypedState<IR>>>::runSearch(
            initialState,
            goalState,
            maxDepth
    );
}

template class AStarSearch<StringState>;

template class AStarSearch<IntegerState>;

template class AStarSearch<NibbleState>;
