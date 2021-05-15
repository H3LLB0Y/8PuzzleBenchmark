#ifndef INC_8PUZZLE_SEARCHALGORITHM_H
#define INC_8PUZZLE_SEARCHALGORITHM_H

#include <string>
#include <list>
#include <set>
#include "../TypedState/TypedState.h"
#include "../InternalRepresentations/InternalRepresentation.h"

struct SearchResults {
    int numberOfStateExpansions;
    int maxQueueLength;
    std::optional<std::string> path;
};

SearchResults makeSearchResults(
        int numberOfStateExpansions,
        int maxQueueLength,
        const std::optional<std::string> &path
);

template<class SearchAlgorithmType>
extern std::string searchAlgorithmTypeName();

template<typename IR, class QT>
class SearchAlgorithm {
public:
    virtual std::string searchAlgorithmTypeName() = 0;

    virtual void addToQueue(QT &queue, TypedState<IR> state, std::set<IR> &alreadyChecked) = 0;

    virtual void addToQueueIfNotAlreadyChecked(QT &queue, TypedState<IR> typedState, std::set<IR> &alreadyChecked);

    virtual bool queueEmpty(QT &queue) = 0;

    virtual int getQueueSize(QT &queue) = 0;

    virtual std::list<MovementType> getSearchDirectionOrder() = 0;

    virtual TypedState<IR> getNext(QT &queue) = 0;

    std::optional<TypedState<IR>> getNextBelowDepth(QT &queue, int &numberOfStateExpansions, int maxDepth);

    virtual
    std::optional<std::string>
    processCurrentState(
            QT &queue,
            TypedState<IR> currentState,
            IR internalGoalState,
            std::set<IR> &alreadyChecked
    );

    virtual SearchResults runSearch(
            const std::string &initialState,
            const std::string &goalState,
            int maxDepth
    );
};

#endif //INC_8PUZZLE_SEARCHALGORITHM_H
