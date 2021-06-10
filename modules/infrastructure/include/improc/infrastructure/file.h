#ifndef IMPROC_INFRASTRUCTURE_FILE_H
#define IMPROC_INFRASTRUCTURE_FILE_H

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#endif

#include <improc/improc_defs.h>
#include <improc/exception.h>

#include <json/json.h>

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>

namespace improc{
    class IMPROC_EXPORTS File
    {
        protected:
            std::string filepath_;

        public:
            File();
            File(const std::string& filepath);

            void                set_filepath(const std::string& filepath);
            
            std::string         get_extension() const;

            std::string         Read();
            bool                Exists() const;

            static std::string  Read    (const std::string& filepath);
            static inline bool  Exists  (const std::string& filepath);
    };

    
    class IMPROC_EXPORTS JsonFile : public File
    {
        public:
            JsonFile();
            JsonFile(const std::string& filepath);

            void                set_filepath(const std::string& filepath);

            Json::Value         Read();
            static Json::Value  Read(const std::string& filepath);

        private:
            static inline bool  IsExtensionValid(const std::string& filepath);
    };
}

#endif
