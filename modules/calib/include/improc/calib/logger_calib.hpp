#ifndef IMPROC_CALIB_LOGGER_CALIB_HPP
#define IMPROC_CALIB_LOGGER_CALIB_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_singleton.hpp>

namespace improc 
{
    /**
     * @brief Logger used for calibration library
     * 
     */
    class IMPROC_API CalibrationLogger final: public LoggerSingleton<CalibrationLogger>
    {
        friend std::shared_ptr<CalibrationLogger> LoggerSingleton::get(const std::string& logger_name);
        private:
            explicit CalibrationLogger(std::shared_ptr<spdlog::logger>&&      logger) : LoggerSingleton(std::move(logger)) {}

        public:
            CalibrationLogger(CalibrationLogger&  that)    = delete;
            CalibrationLogger(CalibrationLogger&& that)    = delete;
            void operator=(const CalibrationLogger&  that) = delete;
            void operator=(const CalibrationLogger&& that) = delete;
    };
}

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define IMPROC_CALIB_LOGGER_TRACE(...) IMPROC_LOGGER_TRACE(improc::CalibrationLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CALIB_LOGGER_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define IMPROC_CALIB_LOGGER_DEBUG(...) IMPROC_LOGGER_DEBUG(improc::CalibrationLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CALIB_LOGGER_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define IMPROC_CALIB_LOGGER_INFO(...) IMPROC_LOGGER_INFO(improc::CalibrationLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CALIB_LOGGER_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define IMPROC_CALIB_LOGGER_WARN(...) IMPROC_LOGGER_WARN(improc::CalibrationLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CALIB_LOGGER_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define IMPROC_CALIB_LOGGER_ERROR(...) IMPROC_LOGGER_ERROR(improc::CalibrationLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CALIB_LOGGER_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define IMPROC_CALIB_LOGGER_CRITICAL(...) IMPROC_LOGGER_CRITICAL(improc::CalibrationLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_CALIB_LOGGER_CRITICAL(...) (void)0
#endif

#endif