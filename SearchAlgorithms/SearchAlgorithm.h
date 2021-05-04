#ifndef INC_8PUZZLE_SEARCHALGORITHM_H
#define INC_8PUZZLE_SEARCHALGORITHM_H

#include <string>
#include <list>
#include "../TypedState/TypedState.h"
#include "../InternalRepresentations/InternalRepresentation.h"

struct SearchResults {
    int numberOfStateExpansions;
    int maxQueueLength;
    std::string path;
};

SearchResults makeSearchResults(
        int numberOfStateExpansions,
        int maxQueueLength,
        std::string path
);

template<class SearchAlgorithmType>
extern std::string searchAlgorithmTypeName();

template<typename IR, class QT>
class SearchAlgorithm {
public:
    virtual void addToQueue(QT &queue, TypedState<IR> state) = 0;

    virtual bool queueEmpty(QT &queue) = 0;

    virtual int getQueueSize(QT &queue) = 0;

    virtual std::list<MovementType> getSearchDirectionOrder() = 0;

    virtual TypedState<IR> getNext(QT &queue) = 0;

    virtual SearchResults runSearch(
            const std::string &initialState,
            const std::string &goalState,
            int maxDepth
    );
};

#endif //INC_8PUZZLE_SEARCHALGORITHM_H
