#include <improc/infrastructure/logger_singleton.h>

template<typename type>
improc::LoggerSingleton<type>::LoggerSingleton(std::shared_ptr<spdlog::logger>&&        logger) : data_(logger) {}

template<typename type>
improc::LoggerSingleton<type>::LoggerSingleton(const std::shared_ptr<spdlog::logger>&   logger) : data_(logger) {}

template<typename type>
std::shared_ptr<spdlog::logger> improc::LoggerSingleton<type>::data()
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Obtaining spdlog logger..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif    
    return this->data_;
}

template<typename type> 
std::shared_ptr<type> improc::LoggerSingleton<type>::get(const std::string& logger_name)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Creating logger..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif    

    static std::shared_ptr<type> singleton = nullptr;
    if (singleton == nullptr)
    {
        std::shared_ptr<spdlog::logger> logger {};
        if (logger_name.empty() == true)
        {
            logger = spdlog::default_logger();
        }
        else
        {
            logger = spdlog::get(logger_name);
            if (logger == nullptr)
            {
                logger = spdlog::stdout_logger_mt(std::move(logger_name));
            }
        }
        singleton = std::shared_ptr<type>(new type(std::move(logger)));
    }
    return singleton;
}
