#ifndef INC_8PUZZLE_PROGRESSIVEDEEPENINGSEARCH_H
#define INC_8PUZZLE_PROGRESSIVEDEEPENINGSEARCH_H


#include <string>

#include "../DepthFirstSearch.h"

template<typename IR>
class ProgressiveDeepeningSearch : public DepthFirstSearch<IR> {
public:
    ProgressiveDeepeningSearch() = default;

    std::string searchAlgorithmTypeName() override;

    SearchResults runSearch(
            const std::string &initialState,
            const std::string &goalState,
            int maxDepth
    ) override;
};

#endif //INC_8PUZZLE_PROGRESSIVEDEEPENINGSEARCH_H
