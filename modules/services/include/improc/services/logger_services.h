#ifndef IMPROC_SERVICES_LOGGER_SERVICES_H
#define IMPROC_SERVICES_LOGGER_SERVICES_H

#include <improc/improc_defs.h>
#include <improc/infrastructure/logger_singleton.h>

namespace improc {
    /**
     * @brief Logger used for services library
     * 
     */
    class IMPROC_EXPORTS ServicesLogger : public LoggerSingleton<ServicesLogger>
    {
        friend std::shared_ptr<ServicesLogger> LoggerSingleton::get(const std::string& logger_name);
        private:
            ServicesLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}

        public:
            ServicesLogger(ServicesLogger&  that)       = delete;
            ServicesLogger(ServicesLogger&& that)       = delete;
            void operator=(const ServicesLogger&  that) = delete;
            void operator=(const ServicesLogger&& that) = delete;
    };
}

#endif