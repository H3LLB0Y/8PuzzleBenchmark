cmake_minimum_required(VERSION 3.2)
project(8Puzzle)

set(CMAKE_CXX_STANDARD 20)

set(
        SOURCE_FILES
        InternalRepresentations/InternalRepresentation.h
        InternalRepresentations/IntegerState/IntegerState.cpp
        InternalRepresentations/IntegerState/IntegerState.h
        InternalRepresentations/NibbleState/NibbleState.cpp
        InternalRepresentations/NibbleState/NibbleState.h
        InternalRepresentations/StringState/StringState.cpp
        InternalRepresentations/StringState/StringState.h
        SearchAlgorithms/SearchAlgorithm.cpp
        SearchAlgorithms/SearchAlgorithm.h
        SearchAlgorithms/AStarSearch/AStarSearch.cpp
        SearchAlgorithms/AStarSearch/AStarSearch.h
        SearchAlgorithms/BreadthFirstSearch/BreadthFirstSearch.cpp
        SearchAlgorithms/BreadthFirstSearch/BreadthFirstSearch.h
        SearchAlgorithms/DepthFirstSearch/DepthFirstSearch.cpp
        SearchAlgorithms/DepthFirstSearch/DepthFirstSearch.h
        SearchAlgorithms/ProgressiveDeepeningSearch/ProgressiveDeepeningSearch.cpp
        SearchAlgorithms/ProgressiveDeepeningSearch/ProgressiveDeepeningSearch.h
        TypedState/TypedState.cpp
        TypedState/TypedState.h
        main.cpp
        TypedState/MovementType.h)
add_executable(main ${SOURCE_FILES})

target_link_libraries(main)
