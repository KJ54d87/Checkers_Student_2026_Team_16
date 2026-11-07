#include <cstdlib> 
#include "Board.h"
#include "StudentAI.h"
#include <gtest/gtest.h>

TEST(AItest, RandomAI) {
     std::system("cd ../../Tools/ && python3 AI_Runner.py 8 8 3 l Sample_AIs/Random_AI/main.py ../src/checkers-cpp/Checker_Teacher > /tmp/log");
}
