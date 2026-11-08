#include <cstdlib> 
#include <fstream> 
#include <string> 
#include "Board.h"
#include "StudentAI.h"
#include <gtest/gtest.h>

TEST(AItest, RandomAI) {
     int winCount = 0;
     const int trials = 100;
     for (int i = 0; i < trials; i++){
          std::system("cd ../../Tools/ && python3 AI_Runner.py 8 8 3 l Sample_AIs/Random_AI/main.py ../src/checkers-cpp/Checker_Teacher | grep -E \"Tie|player\" > /tmp/log");
          std::ifstream log("/tmp/log");
          std::string result; 
          if (log.is_open()){
               std::getline(log, result);
          }
          
          if (result == std::string("player 2 wins")) winCount++;
     } 
     EXPECT_GE(winCount, trials * .6) << "Random AI vs Our AI failed"; 

     winCount = 0;
     for (int i = 0; i < trials; i++){
          std::system("cd ../../Tools/ && python3 AI_Runner.py 8 8 3 l ../src/checkers-cpp/Checker_Teacher Sample_AIs/Random_AI/main.py | grep -E \"Tie|player\" > /tmp/log");
          std::ifstream log("/tmp/log");
          std::string result; 
          if (log.is_open()){
               std::getline(log, result);
          }
          
          if (result == std::string("player 1 wins")) winCount++;
     } 
     EXPECT_GE(winCount, trials * .6) << "Our AI vs Random AI failed"; 
}
