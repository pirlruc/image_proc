#include <improc/infrastructure/file.h>

improc::File::File() {}

improc::File::File(const std::string& filepath) : filepath_(filepath) {}

void improc::File::set_filepath(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Setting filepath {}...",filepath);
    #endif

    this->filepath_ = filepath;
}

std::string improc::File::get_extension() const
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining file extension...");
    #endif

    return std::filesystem::path(this->filepath_).extension().string();
}

std::string improc::File::Read()
{
    return improc::File::Read(this->filepath_);
}

bool improc::File::Exists() const
{
    return improc::File::Exists(this->filepath_);
}

std::string improc::File::Read(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Reading content from filepath {}...",filepath);
    #endif

    if (improc::File::Exists(filepath) == false) {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_01: Filepath {} does not exist.",filepath);
        #endif

        throw improc::invalid_filepath();
    }
 
    std::ifstream file_stream(filepath,std::ifstream::binary);
    if (file_stream.is_open() == false) {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_02: Error opening filepath {}.",filepath);
        #endif

        throw improc::invalid_filepath();
    }

    std::string file_content ( (std::istreambuf_iterator<char>(file_stream))
                             , std::istreambuf_iterator<char>() );
    file_stream.close();
    return file_content;
}

inline bool improc::File::Exists(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Checking if filepath {} exists...",filepath);
    #endif

    struct stat buffer;
    return (stat (filepath.c_str(), &buffer) == 0);
}






improc::JsonFile::JsonFile() : improc::File() {}

improc::JsonFile::JsonFile(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Creating JsonFile object...");
    #endif

    this->set_filepath(filepath);
}

void improc::JsonFile::set_filepath(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Setting json filepath {}...",filepath);
    #endif

    if (improc::JsonFile::IsExtensionValid(filepath) == false)
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error( "ERROR_01: Invalid json extension {}."
                     , improc::File(filepath).get_extension() );
        #endif
        
        throw improc::invalid_filepath();
    }
    this->File::set_filepath(filepath);
}

Json::Value improc::JsonFile::Read()
{
    return improc::JsonFile::Read(this->filepath_);
}

Json::Value improc::JsonFile::Read(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Reading content from json filepath {}...",filepath);
    #endif

    if (improc::JsonFile::IsExtensionValid(filepath) == false)
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error( "ERROR_02: Invalid json extension {}."
                     , improc::File(filepath).get_extension() );
        #endif
        
        throw improc::invalid_filepath();
    }

    std::string json_content = improc::File::Read(filepath);
    
    Json::Value             json_root;
    Json::CharReaderBuilder json_char_builder;
 
    std::unique_ptr<Json::CharReader> json_reader(json_char_builder.newCharReader());
    std::string error;
    bool is_parse_successful = json_reader->parse( json_content.c_str()
                                                 , json_content.c_str() + json_content.length()
                                                 , &json_root
                                                 , &error );
 
    if (is_parse_successful == false) {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_03: Error parsing json file {}: {}.",filepath,error);
        #endif

        throw improc::file_processing_error();
    }
    return json_root;
}

inline bool improc::JsonFile::IsExtensionValid(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Checking if json file {} has valid extension...",filepath);
    #endif
    
    const std::string kJsonExtension = ".json";

    return improc::File(filepath).get_extension() == kJsonExtension;
}






template<typename key_type>
key_type improc::jsonfile::ReadElement(const Json::Value& json_elem)
{
    #ifdef WITH_DEBUG
    SPDLOG_ERROR("");
    spdlog::error("ERROR_04: Parsing not defined for element {}.",typeid(key_type).name());
    #endif

    throw improc::not_supported_data_type();
}

template <>
std::string improc::jsonfile::ReadElement(const Json::Value& json_elem)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Reading string json element...");
    #endif

    return json_elem.asString();
}
