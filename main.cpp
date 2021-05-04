#include <iostream>
#include <chrono>
#include <fstream>
#include "SearchAlgorithms/DepthFirstSearch/DepthFirstSearch.h"
#include "SearchAlgorithms/BreadthFirstSearch/BreadthFirstSearch.h"
#include "SearchAlgorithms/ProgressiveDeepeningSearch/ProgressiveDeepeningSearch.h"
#include "SearchAlgorithms/AStarSearch/AStarSearch.h"

template<typename... Ts, typename F>
constexpr void for_types(F &&f) {
    (f.template operator()<Ts>(), ...);
}

template<typename... Ts, typename F>
constexpr void enumerate_types(F &&f) {
    [&f]<auto... Is>(std::index_sequence<Is...>) {
        (f.template operator()<Ts, Is>(), ...);
    }(std::index_sequence_for<Ts...>{});
}

#define OUTPUT_TO_FILE

int main(int argc, char **argv) {
#ifdef OUTPUT_TO_FILE
    std::ofstream out("results.csv");
    std::cout.rdbuf(out.rdbuf());
#endif

    auto initialStates = {
            "042158367",
            "876543210",
            "481302675",
            "168342750",
            "123804765"
    };
    std::string goalState = "012345678";
    int initialStateIndex = 0;
    for (auto it = initialStates.begin(); it != initialStates.end(); ++it, ++initialStateIndex) {
        auto initialState = *it;
        for_types<
                StringState,
                IntegerState,
                NibbleState
        >([&]<typename IR>() {
            enumerate_types<
                    DepthFirstSearch<IR>,
                    BreadthFirstSearch<IR>,
                    ProgressiveDeepeningSearch<IR>,
                    AStarSearch<IR>
            >([&]<class SA, auto index>() {
                SearchResults searchResults;

                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

                const int NUM_RUNS = 5;
                bool success = true;
                for (int i = 0; i < NUM_RUNS; ++i) {
                    searchResults = SA().runSearch(
                            initialState,
                            goalState,
                            500
                    );
                    if (searchResults.path.empty()) {
                        success = false;
                        break;
                    }
                }

                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::chrono::duration<float, std::milli> duration = end - start;
                std::cout << initialStateIndex << "," << index << ",";
                std::cout << internalRepresentationName<IR>() << ",";
                std::cout << searchAlgorithmTypeName<SA>() << ",";
                std::cout << initialState << ",";
                std::cout << searchResults.maxQueueLength << ",";
                std::cout << searchResults.path.length() << ",";
                std::cout << searchResults.numberOfStateExpansions << ",";
                std::cout << (success ? "Success!" : "Failed...") << ",";
                //std::cout << searchResults.path << ",";
                std::cout << "Time taken = " << duration.count() / (success ? NUM_RUNS : 1) << " milliseconds."
                          << std::endl;
            });
            std::cout << std::endl;
        });
    }
}
