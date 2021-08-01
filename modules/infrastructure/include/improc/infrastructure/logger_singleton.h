#ifndef IMPROC_INFRASTRUCTURE_LOGGER_SINGLETON_H
#define IMPROC_INFRASTRUCTURE_LOGGER_SINGLETON_H

#include <improc/improc_defs.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace improc {
    /**
     * @brief Singleton template for loggers
     * 
     * @tparam type 
     */
    template <typename type>
    class IMPROC_EXPORTS LoggerSingleton
    {
        private:
            std::shared_ptr<spdlog::logger> data_;

        protected:
            LoggerSingleton(std::shared_ptr<spdlog::logger>&&       logger);
            LoggerSingleton(const std::shared_ptr<spdlog::logger>&  logger);
    
        public:
            LoggerSingleton(LoggerSingleton&  that)       = delete;
            LoggerSingleton(LoggerSingleton&& that)       = delete;
            void operator= (const LoggerSingleton&  that) = delete;
            void operator= (const LoggerSingleton&& that) = delete;

            static std::shared_ptr<type>        get(const std::string& logger_name = "");
            std::shared_ptr<spdlog::logger>     data();
    };
}

#endif