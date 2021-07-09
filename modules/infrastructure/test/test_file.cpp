#include <gtest/gtest.h>

#define WITH_DEBUG
#include <improc/infrastructure/file.h>
#include <file.cpp>

TEST(File,TestEmptyFileConstructor) {
    improc::File file_empty {};
    EXPECT_TRUE(file_empty.get_extension().empty());
}

TEST(File,TestFileConstructor) {
    improc::File file_str {"test.txt"};
    EXPECT_STREQ(file_str.get_extension().c_str(),".txt");
}

TEST(File,TestSetFilepath) {
    improc::File file_empty {};
    file_empty.set_filepath("test.txt");
    EXPECT_STREQ(file_empty.get_extension().c_str(),".txt");
}

TEST(File,TestNonExistingFile) {
    improc::File file_not_exists {"test.txt"};
    EXPECT_FALSE(file_not_exists.Exists());
}

TEST(File,TestExistingFile) {
    improc::File file_exists {"../../test/test.json"};
    EXPECT_STREQ(file_exists.get_extension().c_str(),".json");
    EXPECT_TRUE (file_exists.Exists());
}

TEST(File,TestReadingNonExistingFile) {
    improc::File file_not_exists {"test.txt"};
    EXPECT_THROW(file_not_exists.Read(),improc::invalid_filepath);
}

TEST(File,TestReadingExistingFile) {
    improc::File file_exists {"../../test/test.json"};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(JsonFile,TestEmptyFileConstructor) {
    improc::JsonFile file_empty {};
    EXPECT_TRUE(file_empty.get_extension().empty());
}

TEST(JsonFile,TestFileConstructor) {
    improc::JsonFile file_str {"test.json"};
    EXPECT_STREQ(file_str.get_extension().c_str(),".json");
}

TEST(JsonFile,TestNonJsonFileConstructor) {
    EXPECT_THROW(improc::JsonFile file_str {"test.txt"},improc::invalid_filepath);
}

TEST(JsonFile,TestSetFilepath) {
    improc::JsonFile file_empty {};
    file_empty.set_filepath("test.json");
    EXPECT_STREQ(file_empty.get_extension().c_str(),".json");
}

TEST(JsonFile,TestNonJsonSetFilepath) {
    improc::JsonFile not_json_file {};
    EXPECT_THROW(not_json_file.set_filepath("test.txt"),improc::invalid_filepath);
}

TEST(JsonFile,TestNonExistingFile) {
    improc::JsonFile file_not_exists {"test.json"};
    EXPECT_FALSE(file_not_exists.Exists());
}

TEST(JsonFile,TestExistingFile) {
    improc::JsonFile file_exists {"../../test/test.json"};
    EXPECT_STREQ(file_exists.get_extension().c_str(),".json");
    EXPECT_TRUE (file_exists.Exists());
}

TEST(JsonFile,TestReadingNonExistingFile) {
    improc::JsonFile file_not_exists {"test.json"};
    EXPECT_THROW(file_not_exists.Read(),improc::invalid_filepath);
}

TEST(JsonFile,TestReadingExistingFile) {
    improc::JsonFile file_exists {"../../test/test.json"};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(JsonFile,TestReadingNonJsonFile) {
    EXPECT_THROW(improc::JsonFile::Read("test.txt"),improc::invalid_filepath);
}

TEST(JsonFile,TestReadingNonStringContent) {
    improc::JsonFile file_exists {"../../test/test.json"};
    EXPECT_THROW(improc::jsonfile::ReadElement<int>(file_exists.Read()),improc::not_supported_data_type);
}

TEST(JsonFile,TestReadingStringContent) {
    improc::JsonFile file_exists {"../../test/test.json"};
    std::string content = improc::jsonfile::ReadElement<std::string>(file_exists.Read()["content"]);
    EXPECT_FALSE(content.empty());
    EXPECT_STREQ(content.c_str(),"test");
}
