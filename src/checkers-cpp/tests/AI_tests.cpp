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
const std::string poorAI("Sample_AIs/Poor_AI/main.py"); 
const std::string averageAI("Sample_AIs/Average_AI/main.py"); 
const std::string goodAI("Sample_AIs/Good_AI/main.py"); 
const std::string ourAI("../src/checkers-cpp/build/Checker_Teacher");
const int trials = 30;

const double expectedWinrate = 0.6;

std::string buildCommand(std::string AI_1, std::string AI_2){
     std::string command(commandStart);
     command.reserve(AI_1.size() + 1 + AI_2.size() + commandEnd.size());
     command.append(AI_1);
     command.append(" ");
     command.append(AI_2);
     command.append(commandEnd);
     return command;
}

double calcWinrate(std::string AI_1, std::string AI_2, const int trials) {
     int winCount = 0;
     for (int i = 0; i < trials; i++){
          std::system(buildCommand(AI_1, AI_2).c_str());
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
     double winrateRandomVsOur = calcWinrate(randomAI, ourAI, 30);
     EXPECT_GE(winrateRandomVsOur, expectedWinrate) << "Random AI vs Our AI \
failed"; 

     double winrateOurVsRandom = calcWinrate(ourAI, randomAI, 30);
     EXPECT_GE(winrateOurVsRandom, expectedWinrate) << "Our AI vs Random AI \
failed"; 

}

TEST(AItest, PoorAI) {
     double winratePoorVsOur = calcWinrate(poorAI, ourAI, 20);
     EXPECT_GE(winratePoorVsOur, expectedWinrate) << "Poor AI vs Our AI \
failed"; 

     double winrateOurVsPoor = calcWinrate(ourAI, poorAI, 20);
     EXPECT_GE(winrateOurVsPoor, expectedWinrate) << "Our AI vs Poor AI \
failed"; 
}

TEST(AItest, AverageAI) {
     double winrateAverageVsOur = calcWinrate(averageAI, ourAI, 10);
     EXPECT_GE(winrateAverageVsOur, expectedWinrate) << "AverageAI vs Our AI \
failed"; 

     double winrateOurVsAverage = calcWinrate(ourAI, averageAI, 10);
     EXPECT_GE(winrateOurVsAverage, expectedWinrate) << "Our AI vs AverageAI \
failed"; 
}
