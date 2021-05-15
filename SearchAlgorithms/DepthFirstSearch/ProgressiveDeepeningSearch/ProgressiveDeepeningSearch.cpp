#include <iostream>
#include <chrono>
#include "ProgressiveDeepeningSearch.h"

template<typename IR>
std::string ProgressiveDeepeningSearch<IR>::searchAlgorithmTypeName() {
    return "ProgressiveDeepeningSearch";
}

//#define PRINT_TIME_PER_DEPTH

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
#ifdef PRINT_TIME_PER_DEPTH
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
#endif
        // return value from DFS goes into path variable (passing in depth variable as maxDepth for DFS)
        SearchResults newSearchResults = DepthFirstSearch<IR>::runSearch(
                initialState,
                goalState,
                depth
        );

#ifdef PRINT_TIME_PER_DEPTH
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<float> durationSeconds = end - start;
        std::chrono::duration<float, std::milli> durationMillis = end - start;
        std::cout << "Depth: " << depth << " - Time: " << durationMillis.count() << " milliseconds." << std::endl;
#endif

        searchResults.numberOfStateExpansions += newSearchResults.numberOfStateExpansions;
        if (searchResults.maxQueueLength < newSearchResults.maxQueueLength) {
            searchResults.maxQueueLength = newSearchResults.maxQueueLength;
        }
        // check return path for success, if successful break out of loop and return path
        if (newSearchResults.path.has_value()) {
            searchResults.path = newSearchResults.path;
            break;
        }
    }
    return searchResults;
}

template class ProgressiveDeepeningSearch<StringState>;

template class ProgressiveDeepeningSearch<IntegerState>;

template class ProgressiveDeepeningSearch<NibbleState>;
