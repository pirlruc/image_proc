#include <improc/infrastructure/file.h>

improc::File::File() {}

improc::File::File(const std::string& filepath) : filepath_(filepath) {}

void improc::File::set_filepath(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Setting filepath {}..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , filepath );
    #endif

    this->filepath_ = filepath;
}

std::string improc::File::get_filename() const
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Obtaining filename..."
                 , SPDLOG_FUNCTION,__FILE__,__LINE__ );
    #endif

    return std::filesystem::path(this->filepath_).filename().string();
}

std::string improc::File::get_extension() const
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Obtaining file extension..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
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
    spdlog::trace( "[{}:{}:{}] Reading content from filepath {}..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , filepath );
    #endif

    if (improc::File::Exists(filepath) == false) {
        #ifdef WITH_DEBUG
        spdlog::error( "[{}:{}:{}] ERROR_01: Filepath {} does not exist."
                     , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                     , filepath );
        #endif

        throw improc::invalid_filepath();
    }
 
    std::ifstream file_stream(filepath,std::ifstream::binary);
    if (file_stream.is_open() == false) {
        #ifdef WITH_DEBUG
        spdlog::error( "[{}:{}:{}] ERROR_02: Error opening filepath {}."
                     , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                     , filepath );
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
    spdlog::trace( "[{}:{}:{}] Checking if filepath {} exists..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , filepath );
    #endif

    struct stat buffer;
    return (stat (filepath.c_str(), &buffer) == 0);
}






improc::JsonFile::JsonFile() : improc::File() {}

improc::JsonFile::JsonFile(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Creating JsonFile object..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif

    this->set_filepath(filepath);
}

void improc::JsonFile::set_filepath(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Setting json filepath {}..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , filepath );
    #endif

    if (improc::JsonFile::IsExtensionValid(filepath) == false)
    {
        #ifdef WITH_DEBUG
        spdlog::error( "[{}:{}:{}] ERROR_01: Invalid json extension {}."
                     , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
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
    spdlog::trace( "[{}:{}:{}] Reading content from json filepath {}..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , filepath );
    #endif

    if (improc::JsonFile::IsExtensionValid(filepath) == false)
    {
        #ifdef WITH_DEBUG
        spdlog::error( "[{}:{}:{}] ERROR_02: Invalid json extension {}."
                     , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
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
        spdlog::error( "[{}:{}:{}] ERROR_03: Error parsing json file {}: {}."
                     , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                     , filepath,error );
        #endif

        throw improc::file_processing_error();
    }
    return json_root;
}

inline bool improc::JsonFile::IsExtensionValid(const std::string& filepath)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Checking if json file {} has valid extension..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , filepath );
    #endif
    
    const std::string kJsonExtension = ".json";

    return improc::File(filepath).get_extension() == kJsonExtension;
}


template<typename key_type>
key_type improc::jsonfile::ReadElement(const Json::Value& json_elem)
{
    #ifdef WITH_DEBUG
    spdlog::error( "[{}:{}:{}] ERROR_04: Parsing not defined for element {}."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
                 , typeid(key_type).name() );
    #endif

    throw improc::not_supported_data_type();
}

template <>
std::string improc::jsonfile::ReadElement(const Json::Value& json_elem)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Reading string json element..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif

    return json_elem.asString();
}
