#ifndef INC_8PUZZLE_BREADTHFIRSTSEARCH_H
#define INC_8PUZZLE_BREADTHFIRSTSEARCH_H

#include <queue>

#include "../SearchAlgorithm.h"

template<typename IR>
class BreadthFirstSearch : public SearchAlgorithm<IR, std::queue<TypedState<IR>>> {
public:
    BreadthFirstSearch() = default;

    void addToQueue(std::queue<TypedState<IR>> &queue, TypedState<IR> state) override;

    bool queueEmpty(std::queue<TypedState<IR>> &queue) override;

    int getQueueSize(std::queue<TypedState<IR>> &queue) override;

    std::list<MovementType> getSearchDirectionOrder() override;

    TypedState<IR> getNext(std::queue<TypedState<IR>> &queue) override;
};

#endif //INC_8PUZZLE_BREADTHFIRSTSEARCH_H
