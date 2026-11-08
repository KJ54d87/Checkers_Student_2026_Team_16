#include <cstdlib> 
#include <fstream> 
#include <string> 
#include "Board.h"
#include "StudentAI.h"
#include <gtest/gtest.h>

const std::string commandStart("cd ../../Tools/ && python3 AI_Runner.py 8 8 3 \
l ");
const std::string commandEnd(" | grep -E \"Tie|player\" > /tmp/log;");
const std::string randomAI("Sample_AIs/Random_AI/main.py"); 
const std::string ourAI("../src/checkers-cpp/Checker_Teacher");
const int randomTrials = 30;
const double expectedRandomWinrate = 0.6;

std::string buildCommand(std::string AI_1, std::string AI_2){
     std::string command(commandStart);
     command.reserve(AI_1.size() + 1 + AI_2.size() + commandEnd.size());
     command.append(AI_1);
     command.append(" ");
     command.append(AI_2);
     command.append(commandEnd);
     return command;
}

double calcWinrate(std::string AI_1, std::string AI_2) {
     int winCount = 0;
     const int trials = randomTrials;
     std::string command  = buildCommand(AI_1, AI_2);
     
     for (int i = 0; i < trials; i++){
          std::system(command.c_str());
          std::ifstream log("/tmp/log");
          std::string result; 
          if (log.is_open()){
               std::getline(log, result);
          }
          
          if (result == std::string("player 1 wins")) winCount++;
     } 
     return static_cast<double>(winCount)/trials; 
}

TEST(AItest, RandomAI) {
     double winrateRandomVsOur = calcWinrate(randomAI, ourAI);
     EXPECT_GE(winrateRandomVsOur, expectedRandomWinrate) << "Random AI vs Our AI failed"; 

     //EXPECT_GE(winCount, trials * .6) << "Our AI vs Random AI failed"; 
}
