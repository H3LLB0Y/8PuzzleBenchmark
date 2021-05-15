#ifndef INC_8PUZZLE_ASTARSEARCH_H
#define INC_8PUZZLE_ASTARSEARCH_H

#include <map>

#include "../SearchAlgorithm.h"

template<typename IR>
class AStarSearch : public SearchAlgorithm<IR, std::multimap<int, TypedState<IR>>> {
private:
    IR mGoalState;
public:
    AStarSearch() = default;

    std::string searchAlgorithmTypeName() override;

    void addToQueue(
            std::multimap<int, TypedState<IR>> &queue,
            TypedState<IR> state,
            std::set<IR> &alreadyChecked
    ) override;

    void addToQueueIfNotAlreadyChecked(
            std::multimap<int, TypedState<IR>> &queue,
            TypedState<IR> typedState,
            std::set<IR> &alreadyChecked
    ) override;

    bool queueEmpty(std::multimap<int, TypedState<IR>> &queue) override;

    int getQueueSize(std::multimap<int, TypedState<IR>> &queue) override;

    std::list<MovementType> getSearchDirectionOrder() override;

    TypedState<IR> getNext(std::multimap<int, TypedState<IR>> &queue) override;

    SearchResults runSearch(
            const std::string &initialState,
            const std::string &goalState,
            int maxDepth
    ) override;

    std::optional<std::string>
    processCurrentState(
            std::multimap<int, TypedState<IR>> &queue,
            TypedState<IR> currentState,
            IR internalGoalState,
            std::set<IR> &alreadyChecked
    ) override;
};

#endif //INC_8PUZZLE_ASTARSEARCH_H
