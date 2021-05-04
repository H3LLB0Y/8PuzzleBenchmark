#include "SearchAlgorithm.h"

#include <set>
#include <iostream>
#include <stack>
#include <queue>
#include <map>

SearchResults makeSearchResults(
        int numberOfStateExpansions,
        int maxQueueLength,
        std::string path
) {
    SearchResults searchResults;
    searchResults.numberOfStateExpansions = numberOfStateExpansions;
    searchResults.maxQueueLength = maxQueueLength;
    searchResults.path = std::move(path);
    return searchResults;
}

template<typename IR, class QT>
SearchResults SearchAlgorithm<IR, QT>::runSearch(
        const std::string &initialState,
        const std::string &goalState,
        int maxDepth
) {
    int numberOfStateExpansions = 0;
    int maxQueueLength = 0;

    IR internalGoalState = stringToIR<IR>(goalState);
    TypedState<IR> currentState = TypedState<IR>(initialState);
    auto queue = QT();
    addToQueue(queue, currentState);
    auto visited = std::set<IR>();
    visited.insert(currentState.getState());

    while (!queueEmpty(queue)) {
        int queueSize = getQueueSize(queue);
        if (queueSize > maxQueueLength) {
            maxQueueLength = queueSize;
        }

        currentState = getNext(queue);
        ++numberOfStateExpansions;

        if (currentState.getDepth() >= maxDepth) {
            continue;
        }

        for (auto direction : getSearchDirectionOrder()) {
            // TODO: Don't do left if last was right, etc
            if (currentState.canMoveDirection(direction)) {
                auto moved = currentState.moveDirection(direction);
                // check if success
                if (moved == internalGoalState) {
                    return makeSearchResults(
                            numberOfStateExpansions,
                            maxQueueLength,
                            moved.getPath()
                    );
                }
                // if not in the visited list
                IR state = moved.getState();
                if (visited.find(state) == visited.end()) {
                    visited.insert(state);
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
class SearchAlgorithm<StringState, std::stack<TypedState<StringState>>>;

template
class SearchAlgorithm<IntegerState, std::stack<TypedState<IntegerState>>>;

template
class SearchAlgorithm<NibbleState, std::stack<TypedState<NibbleState>>>;

template
class SearchAlgorithm<StringState, std::queue<TypedState<StringState>>>;

template
class SearchAlgorithm<IntegerState, std::queue<TypedState<IntegerState>>>;

template
class SearchAlgorithm<NibbleState, std::queue<TypedState<NibbleState>>>;

template
class SearchAlgorithm<StringState, std::multimap<int, TypedState<StringState>>>;

template
class SearchAlgorithm<IntegerState, std::multimap<int, TypedState<IntegerState>>>;

template
class SearchAlgorithm<NibbleState, std::multimap<int, TypedState<NibbleState>>>;
