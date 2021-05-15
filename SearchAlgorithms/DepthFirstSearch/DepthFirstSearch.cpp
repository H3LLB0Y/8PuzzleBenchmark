#include "DepthFirstSearch.h"

#include <list>

template<typename IR>
std::string DepthFirstSearch<IR>::searchAlgorithmTypeName() {
    return "DepthFirstSearch";
}

template<typename IR>
void DepthFirstSearch<IR>::addToQueue(std::stack<TypedState<IR>> &queue, TypedState<IR> state, std::set<IR> &alreadyChecked) {
    queue.push(state);
    alreadyChecked.insert(state.getState());
}

template<typename IR>
bool DepthFirstSearch<IR>::queueEmpty(std::stack<TypedState<IR>> &queue) {
    return queue.empty();
}

template<typename IR>
int DepthFirstSearch<IR>::getQueueSize(std::stack<TypedState<IR>> &queue) {
    return queue.size();
}

template<typename IR>
TypedState<IR> DepthFirstSearch<IR>::getNext(std::stack<TypedState<IR>> &queue) {
    auto next = queue.top();
    queue.pop();
    return next;
}

template<typename IR>
std::list<MovementType> DepthFirstSearch<IR>::getSearchDirectionOrder() {
    return {
            MovementType::LEFT,
            MovementType::DOWN,
            MovementType::RIGHT,
            MovementType::UP
    };
}

template class DepthFirstSearch<StringState>;

template class DepthFirstSearch<IntegerState>;

template class DepthFirstSearch<NibbleState>;
