/**
 * @brief Construct a new improc::LoggerSingleton<type> object
 * 
 * @tparam type 
 * @param logger 
 */
template<typename type>
improc::LoggerSingleton<type>::LoggerSingleton(std::shared_ptr<spdlog::logger>&&        logger) : data_(std::move(logger)) {}

/**
 * @brief Construct a new improc::LoggerSingleton<type> object
 * 
 * @tparam type 
 * @param logger 
 */
template<typename type>
improc::LoggerSingleton<type>::LoggerSingleton(const std::shared_ptr<spdlog::logger>&   logger) : data_(std::move(logger)) {}

/**
 * @brief Obtain spdlog::logger object associated with improc::LoggerSingleton<type> object
 * 
 * @tparam type 
 * @return std::shared_ptr<spdlog::logger> 
 */
template<typename type>
std::shared_ptr<spdlog::logger> improc::LoggerSingleton<type>::data()
{
    SPDLOG_LOGGER_CALL(spdlog::default_logger(),spdlog::level::trace,"Obtaining spdlog logger...");
    return this->data_;
}

/**
 * @brief Create or get the improc::LoggerSingleton<type> object
 * The spdlog::logger associated with the improc::LoggerSingleton<type> object corresponds to 
 * the logger logger_name. If the logger_name is not provided, the default logger of spdlog is 
 * used. If the logger_name is provided and the logger is not defined, the console is used. 
 * 
 * @tparam type 
 * @param logger_name 
 * @return std::shared_ptr<type> 
 */
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
