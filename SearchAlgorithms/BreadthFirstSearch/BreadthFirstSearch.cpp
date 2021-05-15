#include "BreadthFirstSearch.h"

template<typename IR>
std::string BreadthFirstSearch<IR>::searchAlgorithmTypeName() {
    return "BreadthFirstSearch";
}

template<typename IR>
void BreadthFirstSearch<IR>::addToQueue(
        std::queue<TypedState<IR>> &queue,
        TypedState<IR> state,
        std::set<IR> &alreadyChecked
) {
    queue.push(state);
    alreadyChecked.insert(state.getState());
}

template<typename IR>
bool BreadthFirstSearch<IR>::queueEmpty(std::queue<TypedState<IR>> &queue) {
    return queue.empty();
}

template<typename IR>
int BreadthFirstSearch<IR>::getQueueSize(std::queue<TypedState<IR>> &queue) {
    return queue.size();
}

template<typename IR>
TypedState<IR> BreadthFirstSearch<IR>::getNext(std::queue<TypedState<IR>> &queue) {
    auto next = queue.front();
    queue.pop();
    return next;
}

template<typename IR>
std::list<MovementType> BreadthFirstSearch<IR>::getSearchDirectionOrder() {
    return {
            MovementType::UP,
            MovementType::RIGHT,
            MovementType::DOWN,
            MovementType::LEFT
    };
}

template class BreadthFirstSearch<StringState>;

template class BreadthFirstSearch<IntegerState>;

template class BreadthFirstSearch<NibbleState>;
