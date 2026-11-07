cmake_minimum_required(VERSION 3.14)
project(Checker_Teacher C CXX)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(SOURCE_FILES main.cpp GameLogic.cpp Move.cpp ManualAI.cpp StudentAI.cpp Move.cpp Move.h AI.h Board.cpp)
set(SOURCE_FILES main.cpp Move.cpp Move.h Board.cpp Board.h Checker.cpp Checker.h Utils.cpp Utils.h StudentAI.cpp StudentAI.h GameLogic.cpp GameLogic.h ManualAI.cpp ManualAI.h)

add_executable(Checker_Teacher ${SOURCE_FILES})

#set(SOURCE_FILES main.cpp GameLogic.cpp Move.cpp ManualAI.cpp StudentAI.cpp Move.cpp Move.h AI.h Board.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(src 
  Board.cpp
  Checker.cpp
  GameLogic.cpp
  ManualAI.cpp
  Move.cpp
  StudentAI.cpp
  Utils.cpp
)

enable_testing()

add_executable(
  MCTree_test
  tests/MCTree_tests.cpp
)
target_link_libraries(
  MCTree_test
  src 
  GTest::gtest_main
)

#target_link_libraries(src PRIVATE gtestmain)
target_include_directories(MCTree_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(
  AI_test
  tests/AI_tests.cpp
)
target_link_libraries(
  AI_test
  src 
  GTest::gtest_main
)
target_include_directories(AI_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

include(GoogleTest)
gtest_discover_tests(MCTree_test)
gtest_discover_tests(AI_test)
