#include <improc/infrastructure/file.h>

#include <iostream>

int main()
{
    improc::File file_empty {};
    improc::File file_not_exists {"test.txt"};
    improc::File file_exists {};
    file_exists.set_filepath("../../test/test.json");

    std::cout << "File does not exist: " << file_not_exists.get_extension() 
                                         << " -> " << file_not_exists.Exists() << std::endl;
    std::cout << "File exists        : " << file_exists.get_extension()     
                                         << " -> " << file_exists.Exists()     << std::endl;

    std::cout << "File content       : " << file_exists.Read() << std::endl;


    improc::JsonFile json_file_empty {};
    improc::JsonFile json_file_not_exists {"test.json"};
    improc::JsonFile json_file_exists {};
    json_file_exists.set_filepath("../../test/test.json");

    std::cout << "File does not exist: " << json_file_not_exists.get_extension() 
                                         << " -> " << json_file_not_exists.Exists() << std::endl;
    std::cout << "File exists        : " << json_file_exists.get_extension()     
                                         << " -> " << json_file_exists.Exists()     << std::endl;

    std::cout << "File content       : " << json_file_exists.Read() << std::endl;
    
    // improc::JsonFile not_json_file {"test.txt"};
    // json_file_exists.set_filepath("test.txt");
    // improc::JsonFile::Read("test.txt");
     return 0;
}