#include "ProgressiveDeepeningSearch.h"

template<typename IR>
SearchResults ProgressiveDeepeningSearch<IR>::runSearch(
        const std::string &initialState,
        const std::string &goalState,
        int maxDepth
) {
    // return string variable path
    SearchResults searchResults;
    searchResults.numberOfStateExpansions = 0;
    searchResults.maxQueueLength = 0;
    searchResults.path = "";
    // iterate through from depth 1 to depth maxDepth
    for (int depth = 1; depth <= maxDepth; ++depth) {
        // return value from DFS goes into path variable (passing in depth variable as maxDepth for DFS)
        SearchResults newSearchResults = DepthFirstSearch<IR>::runSearch(
                initialState,
                goalState,
                depth
        );
        searchResults.numberOfStateExpansions += newSearchResults.numberOfStateExpansions;
        if (searchResults.maxQueueLength < newSearchResults.maxQueueLength) {
            searchResults.maxQueueLength = newSearchResults.maxQueueLength;
        }
        // check return path for success, if successful break out of loop and return path
        if (!newSearchResults.path.empty()) {
            searchResults.path = newSearchResults.path;
            break;
        }
    }
    return searchResults;
}

template
class ProgressiveDeepeningSearch<StringState>;

template
class ProgressiveDeepeningSearch<IntegerState>;

template
class ProgressiveDeepeningSearch<NibbleState>;


template<>
std::string searchAlgorithmTypeName<ProgressiveDeepeningSearch<StringState>>() {
    return "ProgressiveDeepeningSearch";
}

template<>
std::string searchAlgorithmTypeName<ProgressiveDeepeningSearch<IntegerState>>() {
    return "ProgressiveDeepeningSearch";
}

template<>
std::string searchAlgorithmTypeName<ProgressiveDeepeningSearch<NibbleState>>() {
    return "ProgressiveDeepeningSearch";
}
