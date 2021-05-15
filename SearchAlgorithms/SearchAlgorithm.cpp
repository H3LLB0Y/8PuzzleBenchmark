#include "SearchAlgorithm.h"

#include <map>
#include <queue>
#include <set>
#include <stack>

SearchResults makeSearchResults(
        int numberOfStateExpansions,
        int maxQueueLength,
        const std::optional<std::string> &path
) {
    SearchResults searchResults;
    searchResults.numberOfStateExpansions = numberOfStateExpansions;
    searchResults.maxQueueLength = maxQueueLength;
    searchResults.path = path.has_value() ? path : std::nullopt;
    return searchResults;
}

template<typename IR, class QT>
void SearchAlgorithm<IR, QT>::addToQueueIfNotAlreadyChecked(
        QT &queue,
        TypedState<IR> typedState,
        std::set<IR> &alreadyChecked
) {
    auto state = typedState.getState();
    if (alreadyChecked.find(state) == alreadyChecked.end()) {
        addToQueue(queue, typedState, alreadyChecked);
    }
}

template<typename IR, class QT>
std::optional<TypedState<IR>>
SearchAlgorithm<IR, QT>::getNextBelowDepth(
        QT &queue,
        int &numberOfStateExpansions,
        int maxDepth
) {
    while (!queueEmpty(queue)) {
        auto currentState = getNext(queue);
        if (currentState.getDepth() < maxDepth) {
            ++numberOfStateExpansions;
            return currentState;
        }
    }
    return std::nullopt;
}

template<typename IR, class QT>
std::optional<std::string> SearchAlgorithm<IR, QT>::processCurrentState(
        QT &queue,
        TypedState<IR> currentState,
        IR internalGoalState,
        std::set<IR> &alreadyChecked
) {
    for (auto direction : this->getSearchDirectionOrder()) {
        // TODO: Don't do left if last was right, etc
        if (currentState.canMoveDirection(direction)) {
            auto moved = currentState.moveDirection(direction);
            // check if success
            if (moved == internalGoalState) {
                return moved.getPath();
            }
            // if not in the alreadyChecked list
            this->addToQueueIfNotAlreadyChecked(queue, moved, alreadyChecked);
        }
    }
    return std::nullopt;
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
    auto alreadyChecked = std::set<IR>();

    addToQueue(queue, currentState, alreadyChecked);

    while (!queueEmpty(queue)) {
        int queueSize = getQueueSize(queue);
        if (queueSize > maxQueueLength) {
            maxQueueLength = queueSize;
        }

        std::optional<TypedState<IR>> nextCurrentState = getNextBelowDepth(
                queue,
                numberOfStateExpansions,
                maxDepth
        );

        if (nextCurrentState.has_value()) {
            currentState = nextCurrentState.value();
        } else {
            // Queue is empty, break and return fail
            break;
        }

        std::optional<std::string> results = processCurrentState(
                queue,
                currentState,
                internalGoalState,
                alreadyChecked
        );
        if (results.has_value()) {
            return makeSearchResults(
                    numberOfStateExpansions,
                    maxQueueLength,
                    results.value()
            );
        }
    }

    // Q is empty return empty path, No solution found! :'(
    return makeSearchResults(
            numberOfStateExpansions,
            maxQueueLength,
            std::nullopt
    );
}

template class SearchAlgorithm<StringState, std::stack<TypedState<StringState>>>;
template class SearchAlgorithm<StringState, std::queue<TypedState<StringState>>>;
template class SearchAlgorithm<StringState, std::multimap<int, TypedState<StringState>>>;

template class SearchAlgorithm<IntegerState, std::stack<TypedState<IntegerState>>>;
template class SearchAlgorithm<IntegerState, std::queue<TypedState<IntegerState>>>;
template class SearchAlgorithm<IntegerState, std::multimap<int, TypedState<IntegerState>>>;

template class SearchAlgorithm<NibbleState, std::stack<TypedState<NibbleState>>>;
template class SearchAlgorithm<NibbleState, std::queue<TypedState<NibbleState>>>;
template class SearchAlgorithm<NibbleState, std::multimap<int, TypedState<NibbleState>>>;
