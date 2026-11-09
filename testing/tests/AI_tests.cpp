#include <cstdlib> 
#include <fstream> 
#include <string> 
#include "Board.h"
#include "StudentAI.h"
#include <gtest/gtest.h>

const std::string commandStart("cd ../Tools/ && python3 AI_Runner.py 8 8 3 \
l ");
const std::string commandEnd(" | grep -E \"Tie|player\" > /tmp/log;");
const std::string randomAI("Sample_AIs/Random_AI/main.py"); 
const std::string poorAI("Sample_AIs/Poor_AI/main.py"); 
const std::string averageAI("Sample_AIs/Average_AI/main.py"); 
const std::string goodAI("Sample_AIs/Good_AI/main.py"); 
const std::string ourAI("../testing/build/OurAI");
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

TEST(AItest, RandomVsOur) {
     double winrateRandomVsOur = calcWinrate(randomAI, ourAI, 10);
     EXPECT_GE(winrateRandomVsOur, expectedWinrate) << "Random AI vs Our AI \
failed"; 
}
TEST(AItest, OurVsRandom) {
     double winrateOurVsRandom = calcWinrate(ourAI, randomAI, 10);
     EXPECT_GE(winrateOurVsRandom, expectedWinrate) << "Our AI vs Random AI \
failed"; 
}

TEST(AItest, OurVsPoor) {
     double winrateOurVsPoor = calcWinrate(ourAI, poorAI, 10);
     EXPECT_GE(winrateOurVsPoor, expectedWinrate) << "Our AI vs Poor AI \
failed"; 
}

TEST(AItest, OurVsAverage) {
     double winrateOurVsAverage = calcWinrate(ourAI, averageAI, 5);
     EXPECT_GE(winrateOurVsAverage, expectedWinrate) << "Our AI vs AverageAI \
failed"; 
}
