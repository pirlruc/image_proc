#include <improc/infrastructure/logger_singleton.h>

template<typename type>
improc::LoggerSingleton<type>::LoggerSingleton(std::shared_ptr<spdlog::logger>&&        logger) : data_(logger) {}

template<typename type>
improc::LoggerSingleton<type>::LoggerSingleton(const std::shared_ptr<spdlog::logger>&   logger) : data_(logger) {}

template<typename type>
std::shared_ptr<spdlog::logger> improc::LoggerSingleton<type>::data()
{
    SPDLOG_LOGGER_CALL(spdlog::default_logger(),spdlog::level::trace,"Obtaining spdlog logger...");
    return this->data_;
}

template<typename type> 
std::shared_ptr<type> improc::LoggerSingleton<type>::get(const std::string& logger_name)
{
    SPDLOG_LOGGER_CALL(spdlog::default_logger(),spdlog::level::trace,"Creating logger...");
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
                logger = spdlog::stdout_color_mt(std::move(logger_name));
                logger->set_level(spdlog::level::debug);
                logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%n] [%^%-8l%$] [%!:%@] %v");
            }
        }
        singleton = std::shared_ptr<type>(new type(std::move(logger)));
    }
    return singleton;
}
