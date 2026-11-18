#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "CreateAI.h"
#include <gtest/gtest.h>

std::filesystem::directory_entry DEFAULT_TEST_DIR 
     {std::filesystem::path ("/tmp/Group16Compsci161TestDir")};

std::filesystem::directory_entry SRC_DIR 
     {std::filesystem::path ("../src/checkers-cpp")};

std::filesystem::directory_entry create_uncontested_tmp_dir(){
     std::filesystem::directory_entry new_tmp_dir{DEFAULT_TEST_DIR}; 
     int filler = 1;

     while (!std::filesystem::create_directory(new_tmp_dir)){
          //Cursed one liner to generate alternative directories
          new_tmp_dir.replace_filename(
               std::filesystem::path{
                    DEFAULT_TEST_DIR.path().string() + std::to_string(filler++)
               });
     }
     return new_tmp_dir;
}

TEST(CreateAITest, create_AI_copies_src) {
     auto work_dir = create_uncontested_tmp_dir();
     fs::path mock_config_file_path = work_dir.path() / "tmp";
     std::ofstream mock_config_file{mock_config_file_path};

     create_AI(work_dir, "create_AI_copies_src", mock_config_file_path);
     
     for (auto file : fs::directory_iterator(SRC_DIR)){
          EXPECT_TRUE(fs::exists((work_dir/ fs::path(file).filename())));
     }
}

TEST(CreateAITest, applies_changes) {
     auto work_dir = create_uncontested_tmp_dir();
     fs::path mock_config_file_path = work_dir.path() / "config.txt";
     std::ofstream mock_config_file{mock_config_file_path};
     mock_config_file << "DRAW_REWARD 0.7\n";
     mock_config_file.close();

     create_AI(work_dir, "create_AI_copies_src", mock_config_file_path);
     
     std::ifstream StudentAIHeader{work_dir.path() / "StudentAI.h"};

     std::string line;
     while (std::getline(StudentAIHeader, line)){
          if (line.find("DRAW_REWARD") != std::string::npos){
               EXPECT_TRUE(line.find("DRAW_REWARD{0.7") != std::string::npos) 
                    << "Expected DRAW_REWARD{0.7}, got: " << line;
               //We could do more complicated matching but I can't be bothered
               // Future dev, keep in mind that this testcase is necessary but
               // not sufficient. 
          }          
     }
}

TEST(CreateAITest, simulate_game_lobotomized_AI_should_lose) {
     auto normal_AI_dir = create_uncontested_tmp_dir();
     auto dumb_AI_dir = create_uncontested_tmp_dir();

     fs::path normal_config_path = normal_AI_dir.path() / "config.txt";
     std::ofstream normal_config_file{normal_config_path};
     normal_config_file.close();

     fs::path dumb_config_path = dumb_AI_dir.path() / "config.txt";
     std::ofstream dumb_config_file{dumb_config_path};
     dumb_config_file << "SIMULATIONS 10\n";
     dumb_config_file.close();

     create_AI(normal_AI_dir, "normal_AI", normal_config_path);
     create_AI(dumb_AI_dir, "dumb_AI", dumb_config_path);
     
     bool NormalAIWins = simulate_game(normal_AI_dir.path() / "main.cpp", 
          dumb_AI_dir.path() / "main.cpp");


     EXPECT_TRUE(NormalAIWins);
}
