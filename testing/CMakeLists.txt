cmake_minimum_required(VERSION 3.14)
project(Checker_Teacher C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES ../src/checkers-cpp/main.cpp ../src/checkers-cpp/GameLogic.cpp ../src/checkers-cpp/Move.cpp ../src/checkers-cpp/ManualAI.cpp ../src/checkers-cpp/StudentAI.cpp ../src/checkers-cpp/Move.cpp ../src/checkers-cpp/Move.h ../src/checkers-cpp/AI.h ../src/checkers-cpp/Board.cpp ../src/checkers-cpp/Board.cpp ../src/checkers-cpp/Board.h ../src/checkers-cpp/Utils.cpp ../src/checkers-cpp/Utils.h ../src/checkers-cpp/Checker.h ../src/checkers-cpp/Checker.cpp)
# Yes, doing a reletive path is very fragile and will break if we move any 
# files. However, due to the assignment, we are constrained to not move any
# files. 

add_executable(OurAI ${SOURCE_FILES})


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(src 
  ../src/checkers-cpp/Board.cpp
  ../src/checkers-cpp/Checker.cpp
  ../src/checkers-cpp/GameLogic.cpp
  ../src/checkers-cpp/ManualAI.cpp
  ../src/checkers-cpp/Move.cpp
  ../src/checkers-cpp/StudentAI.cpp
  ../src/checkers-cpp/Utils.cpp
)

enable_testing()

add_executable(
  AI_test
  tests/AI_tests.cpp
)
target_link_libraries(
  AI_test
  src 
  GTest::gtest_main
)
target_include_directories(AI_test PUBLIC "../src/checkers-cpp" "${CMAKE_CURRENT_BINARY_DIR}")

include(GoogleTest)
#gtest_discover_tests(MCTree_test)
gtest_discover_tests(AI_test)
