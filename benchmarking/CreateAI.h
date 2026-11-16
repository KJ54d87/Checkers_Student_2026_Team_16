#include <cstdlib> 
#include <string> 
#include <iostream>
#include <filesystem>

const std::string replaceStart("sed -i ");
const std::string commandStart("cd ../Tools/ && python3 AI_Runner.py 8 8 3 \
l ");
const std::string ourAI("../testing/build/OurAI");
const int trials = 30;
const std::filesystem::directory_entry source_directory{std::filesystem::path( 
     "../src/checkers-cpp")};
const std::filesystem::directory_entry temp{"/tmp"};

bool simulate_game(std::string AI_1, std::string AI_2, int expected_winner=1);

void copy_files(std::filesystem::path from, std::filesystem::path to);

std::filesystem::path create_AI(std::filesystem::directory_entry location, 
     std::string name, std::filesystem::path config);
