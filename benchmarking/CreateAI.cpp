#include <cstdlib> 
#include <string> 
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

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

bool simulate_game(fs::path AI_1, fs::path AI_2){
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

void create_AI(std::filesystem::directory_entry location, 
     std::string name, std::filesystem::path config) {
     //copy to temp
     fs::copy(source_directory, location, fs::copy_options::recursive);
     //sed
     std::ifstream config_file{config};
     std::string variable;
     float value;

     //sed -i 's/DRAW_REWARD.*/DRAW_REWARD{0.7};/' StudentAI.h 
     while (config_file >> variable >> value){
          std::system(
               (replaceStart + " 's/" 
               + variable + ".*/"
               + variable + "{" + std::to_string(value) + "};/' "
               + fs::canonical(fs::path(location) / "StudentAI.h").string())
               .c_str());
     }
     //make
     std::system(
          ("cd " + fs::canonical(fs::path(location)).string()
          + " && make >> build_log").c_str()
     );
}
