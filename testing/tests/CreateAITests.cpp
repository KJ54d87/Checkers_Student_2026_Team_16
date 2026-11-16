#include <iostream>
#include <filesystem>
#include <string>
#include "CreateAI.h"
#include <gtest/gtest.h>

std::filesystem::directory_entry DEFAULT_TEST_DIR 
     {std::filesystem::path ("/tmp/Group16Compsci161TestDir")};

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

TEST(CreateAITest, copy_files_move_one_file_to_tmp) {
     // Create a test_dir in tmp
     // Create a file in test_dir
     // Create a copy_to_dir in test_dir
     // Copy file from test_dir to copy_to_dir
     // Check if file is in copy_to_dir
     // Delete test_dir, otherwise we break future tets cases
     create_uncontested_tmp_dir();
     
}

TEST(CreateAITest, copy_files_move_one_dir_to_tmp) {
     // Create a directory + 2 files
     // Move to tmp
     // Check if directory + files are in tmp
     
}
