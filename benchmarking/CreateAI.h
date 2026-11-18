#include <cstdlib> 
#include <string> 
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

const std::string replaceStart("sed -i ");
const std::string commandStart("cd ../Tools/ && python3 AI_Runner.py 8 8 3 \
l ");
const std::string ourAI("../testing/build/OurAI");
const int trials = 30;
const std::filesystem::directory_entry source_directory{std::filesystem::path( 
     "../src/checkers-cpp")};
const std::filesystem::directory_entry temp{"/tmp"};

bool simulate_game(fs::path AI_1, fs::path AI_2);

void create_AI(std::filesystem::directory_entry location, 
     std::string name, std::filesystem::path config);
