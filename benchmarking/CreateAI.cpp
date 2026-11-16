#include <cstdlib> 
#include <string> 
#include <iostream>
#include <filesystem>

namespace fs=std::filesystem;

//sed -i 's/DRAW_REWARD.*/DRAW_REAWD{0.7};/' StudentAI.h 
const std::string replaceStart("sed -i ");
const std::string commandStart("cd ../Tools/ && python3 AI_Runner.py 8 8 3 \
l ");
const std::string ourAI("../testing/build/OurAI");
const int trials = 30;
const std::filesystem::directory_entry source_directory{std::filesystem::path( 
     "../src/checkers-cpp")};
const std::filesystem::directory_entry temp{"/tmp"};

bool simulate_game(std::string AI_1, std::string AI_2, int expected_winner=1){
     //std::system();
     //std::ifstream log("/tmp/log");
     //std::string result; 
     //if (log.is_open()){
     //     std::getline(log, result);
     //}

     //if (expected_winner == 1 && result == std::string("player 1 wins")) return true;
     //if (expected_winner == 2 && result == std::string("player 2 wins")) return true;
     //return false;
}

void copy_files(std::filesystem::path from, std::filesystem::path to){
     //std::system("cp -r " + std::filesystem::absolute(from) + " " + \
     //std::filesystem::absolute(to));
}

std::filesystem::path create_AI(std::filesystem::directory_entry location, 
     std::string name, std::filesystem::path config) {
     //copy to temp
     fs::copy(source_directory, location, fs::copy_options::recursive);
     //sed
     //make
     //move to 
     return source_directory;
}
