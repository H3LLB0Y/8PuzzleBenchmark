#include "SearchAlgorithms/DepthFirstSearch/DepthFirstSearch.h"
#include "SearchAlgorithms/BreadthFirstSearch/BreadthFirstSearch.h"
#include "SearchAlgorithms/DepthFirstSearch/ProgressiveDeepeningSearch/ProgressiveDeepeningSearch.h"
#include "SearchAlgorithms/AStarSearch/AStarSearch.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <utility>

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

//#define OUTPUT_TO_FILE
#define PRINT_PATH

int main(int argc, char **argv) {
#ifdef OUTPUT_TO_FILE
    std::ofstream out("results.csv");
    std::cout.rdbuf(out.rdbuf());
#endif

    auto initialStates = {
            "042158367",
            "876543210",
            "481302675",
            "168342750"
            //,"123804765" // Note: No solution found so takes very long time on PDS
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

                const int NUM_RUNS = 1;//000000;
                const int MAX_RUN_SECONDS = 30;
                int actualRuns;
                bool success = true;
                bool timeout = false;
                for (actualRuns = 0; actualRuns < NUM_RUNS; ++actualRuns) {
                    searchResults = SA().runSearch(
                            initialState,
                            goalState,
                            500
                    );
                    if (!searchResults.path.has_value()) {
                        success = false;
                        break;
                    }
                    std::chrono::steady_clock::time_point timeCheck = std::chrono::steady_clock::now();
                    std::chrono::duration<float> runningTime = timeCheck - start;
                    if (runningTime > std::chrono::seconds(MAX_RUN_SECONDS)) {
                        timeout = true;
                        break;
                    }
                }

                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::chrono::duration<float> durationSeconds = end - start;
                std::chrono::duration<float, std::milli> durationMillis = end - start;
                std::cout << initialStateIndex << "," << index << ",";
                std::cout << internalRepresentationName<IR>() << ",";
                // TODO: I don't like this, shouldn't need to instantiate the class to get it's name! :@
                // TODO: Looking for some C++ Magic to make this happen
                std::cout << SA().searchAlgorithmTypeName() << ",";
                std::cout << initialState << ",";
                std::cout << searchResults.maxQueueLength << ",";
                if (searchResults.path.has_value()) {
                    std::cout << searchResults.path.value().length() << ",";
                } else {
                    std::cout << "NO PATH,";
                }
                std::cout << searchResults.numberOfStateExpansions << ",";
                std::cout << (success ? (timeout ? "Timeout?" : "Success!") : "Failed...") << ",";
#ifdef PRINT_PATH
                if (searchResults.path.has_value()) {
                    std::cout << searchResults.path.value() << ",";
                } else {
                    std::cout << "NO PATH,";
                }
#endif
                std::cout << actualRuns << " runs in " << durationSeconds.count() << " secs" << ",";
                std::cout << "Time taken = " << durationMillis.count() / (success ? actualRuns : 1) << " ms."
                          << std::endl;
            });
            std::cout << std::endl;
        });
    }
}
