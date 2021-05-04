#ifndef INC_8PUZZLE_DEPTHFIRSTSEARCH_H
#define INC_8PUZZLE_DEPTHFIRSTSEARCH_H

#include <stack>
#include "../SearchAlgorithm.h"

template<typename IR>
class DepthFirstSearch : public SearchAlgorithm<IR, std::stack<TypedState<IR>>> {
public:
    DepthFirstSearch() = default;

    void addToQueue(std::stack<TypedState<IR>> &queue, TypedState<IR> state) override;

    bool queueEmpty(std::stack<TypedState<IR>> &queue) override;

    int getQueueSize(std::stack<TypedState<IR>> &queue) override;

    std::list<MovementType> getSearchDirectionOrder() override;

    TypedState<IR> getNext(std::stack<TypedState<IR>> &queue) override;
};

#endif //INC_8PUZZLE_DEPTHFIRSTSEARCH_H
