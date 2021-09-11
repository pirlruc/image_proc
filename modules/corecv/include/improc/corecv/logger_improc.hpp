#ifndef IMPROC_CORECV_LOGGER_IMPROC_HPP
#define IMPROC_CORECV_LOGGER_IMPROC_HPP

#include <improc/improc_defs.hpp>
#include <servproc/infrastructure/logger_singleton.hpp>

namespace improc {
    /**
     * @brief Logger used for image processing library
     * 
     */
    class IMPROC_EXPORTS ImageProcLogger : public servproc::LoggerSingleton<ImageProcLogger>
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