#ifndef IMPROC_CORECV_LOGGER_IMPROC_H
#define IMPROC_CORECV_LOGGER_IMPROC_H

#include <improc/improc_defs.h>
#include <improc/infrastructure/logger_singleton.h>

namespace improc {
    /**
     * @brief Logger used for image processing library
     * 
     */
    class IMPROC_EXPORTS ImageProcLogger : public LoggerSingleton<ImageProcLogger>
    {
        friend std::shared_ptr<ImageProcLogger> LoggerSingleton::get(const std::string& logger_name);
        private:
            ImageProcLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}

        public:
            ImageProcLogger(ImageProcLogger&  that)       = delete;
            ImageProcLogger(ImageProcLogger&& that)       = delete;
            void operator=(const ImageProcLogger&  that)  = delete;
            void operator=(const ImageProcLogger&& that)  = delete;
    };
}

#endif