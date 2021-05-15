cmake_minimum_required(VERSION 3.2)
project(8Puzzle)

set(
        SOURCE_FILES
        8Puzzle.cpp
        InternalRepresentations/InternalRepresentation.h
        InternalRepresentations/IntegerState/IntegerState.cpp
        InternalRepresentations/IntegerState/IntegerState.h
        InternalRepresentations/NibbleState/NibbleState.cpp
        InternalRepresentations/NibbleState/NibbleState.h
        InternalRepresentations/StringState/StringState.cpp
        InternalRepresentations/StringState/StringState.h
        SearchAlgorithms/AStarSearch/AStarSearch.cpp
        SearchAlgorithms/AStarSearch/AStarSearch.h
        SearchAlgorithms/BreadthFirstSearch/BreadthFirstSearch.cpp
        SearchAlgorithms/BreadthFirstSearch/BreadthFirstSearch.h
        SearchAlgorithms/DepthFirstSearch/DepthFirstSearch.cpp
        SearchAlgorithms/DepthFirstSearch/DepthFirstSearch.h
        SearchAlgorithms/DepthFirstSearch/ProgressiveDeepeningSearch/ProgressiveDeepeningSearch.cpp
        SearchAlgorithms/DepthFirstSearch/ProgressiveDeepeningSearch/ProgressiveDeepeningSearch.h
        SearchAlgorithms/SearchAlgorithm.cpp
        SearchAlgorithms/SearchAlgorithm.h
        TypedState/TypedState.cpp
        TypedState/TypedState.h
        TypedState/MovementType.cpp
        TypedState/MovementType.h
)
add_executable(8Puzzle ${SOURCE_FILES})
target_compile_features(8Puzzle PRIVATE cxx_std_17)
