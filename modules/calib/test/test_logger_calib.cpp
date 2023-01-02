#include <gtest/gtest.h>

#include <improc/calib/logger_calib.hpp>

TEST(LoggerCalib,TestLoggerLogging) {
    improc::CalibrationLogger::get("calib_logger");
    EXPECT_STREQ(improc::CalibrationLogger::get()->data()->name().c_str(),"calib_logger");
    IMPROC_CALIB_LOGGER_TRACE("Test {} {}",1,2);
    IMPROC_CALIB_LOGGER_DEBUG("Test {} {}",2,3);
    IMPROC_CALIB_LOGGER_INFO ("Test {} {}",3,4);
    IMPROC_CALIB_LOGGER_ERROR("Test {} {}",4,5);
    IMPROC_CALIB_LOGGER_WARN ("Test {} {}",5,6);
    IMPROC_CALIB_LOGGER_CRITICAL("Test {} {}",6,7);
}
