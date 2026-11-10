#include <cstdlib> 
#include <fstream> 
#include <string> 
#include <thread>
#include <future>
#include <iostream>
#include <stdexcept>
#include <chrono>
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
//const int cores = std::thread::hardware_concurrency();
const int cores = 2;

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

bool simulate_game(std::string AI_1, std::string AI_2, int expected_winner=1){
     std::system(buildCommand(AI_1, AI_2).c_str());
     std::ifstream log("/tmp/log");
     std::string result; 
     if (log.is_open()){
          std::getline(log, result);
     }

     if (expected_winner == 1 && result == std::string("player 1 wins")) return true;
     if (expected_winner == 2 && result == std::string("player 2 wins")) return true;
     return false;
}

double calcWinrate(std::string AI_1, std::string AI_2, const int trials, int expected_winner=1) {
    if (expected_winner != 1 && expected_winner != 2) throw range_error("Called with an expected winner that is not 1 or 2");
    if (cores == 0){
        int winCount = 0;
          for (int i = 0; i < trials; i++){
               if (simulate_game(AI_1, AI_2, expected_winner)) winCount++;
          } 
          return static_cast<double>(winCount)/trials; 
    } else {
        int winCount = 0;
        std::packaged_task<bool(std::string,std::string,int)>task(&simulate_game);
        std::packaged_task<bool(std::string,std::string,int)>task2(&simulate_game);
            auto result = task.get_future();
        auto result2 = task2.get_future();
        std::thread t(std::move(task), AI_1, AI_2, 1);
        std::thread t2(std::move(task2), AI_1, AI_2, 1);
        t.join();
        t2.join();
        if (result.get()) winCount++;
        if (result2.get()) winCount++;
        return static_cast<double>(winCount)/trials; 
    }
}

TEST(AIBenchmark, ThreadedIsFasterThanSerial) {
    const auto startSerial = std::chrono::steady_clock::now();
    double winrateRandomVsOur = calcWinrate(randomAI, ourAI, 1, 2);
    winrateRandomVsOur = calcWinrate(randomAI, ourAI, 1, 2);
    const auto endSerial = std::chrono::steady_clock::now();

    const auto startConcurrent = std::chrono::steady_clock::now();
    winrateRandomVsOur = calcWinrate(randomAI, ourAI, 2, 2);
    const auto endConcurrent = std::chrono::steady_clock::now();
    
    auto serialTime = endSerial - startSerial;
    auto concurrentTime = endConcurrent - startConcurrent;
       
    EXPECT_LE(concurrentTime.count(), serialTime.count());
    std::cout<<std::endl<<static_cast<double>(serialTime.count())/concurrentTime.count()<<" speedup"<<std::endl;
}

TEST(AItest, RandomVsOur) {
     double winrateRandomVsOur = calcWinrate(randomAI, ourAI, 1, 2);
     EXPECT_GE(winrateRandomVsOur, expectedWinrate) << "Random AI vs Our AI \
failed"; 
}
TEST(AItest, OurVsRandom) {
     double winrateOurVsRandom = calcWinrate(ourAI, randomAI, 1);
     EXPECT_GE(winrateOurVsRandom, expectedWinrate) << "Our AI vs Random AI \
failed"; 
}

TEST(AItest, OurVsPoor) {
     double winrateOurVsPoor = calcWinrate(ourAI, poorAI, 1);
     EXPECT_GE(winrateOurVsPoor, expectedWinrate) << "Our AI vs Poor AI \
failed"; 
}

TEST(AItest, OurVsAverage) {
     double winrateOurVsAverage = calcWinrate(ourAI, averageAI, 1);
     EXPECT_GE(winrateOurVsAverage, expectedWinrate) << "Our AI vs AverageAI \
failed"; 
}
