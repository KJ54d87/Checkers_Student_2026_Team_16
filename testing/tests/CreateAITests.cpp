#include <iostream>
#include <filesystem>
#include <string>
#include "CreateAI.h"
#include <gtest/gtest.h>

std::filesystem::directory_entry DEFAULT_TEST_DIR 
     {std::filesystem::path ("/tmp/Group16Compsci161TestDir")};

std::filesystem::directory_entry create_uncontested_tmp_dir(){
     std::filesystem::create_directory(DEFAULT_TEST_DIR);
     return DEFAULT_TEST_DIR;
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
