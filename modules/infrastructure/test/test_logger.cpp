#include <gtest/gtest.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <iostream>

TEST(Logger,TestLogging) {
    EXPECT_NO_THROW(
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%-5l] [%@ >> %!] %v");
        spdlog::set_default_logger(spdlog::stdout_logger_mt("console"));
        spdlog::set_level(spdlog::level::level_enum::trace);
    );
}