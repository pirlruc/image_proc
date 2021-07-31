#include <gtest/gtest.h>

#include <improc/infrastructure/logger_singleton.h>
#include <logger_singleton.cpp>

class TestLoggerReference : public improc::LoggerSingleton<TestLoggerReference>
{
    public:
        TestLoggerReference(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(logger) {}
};

class TestLoggerMove : public improc::LoggerSingleton<TestLoggerMove>
{
    public:
        TestLoggerMove(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

class TestExistingLogger : public improc::LoggerSingleton<TestExistingLogger>
{
    public:
        TestExistingLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

class TestDoubleLogger : public improc::LoggerSingleton<TestDoubleLogger>
{
    public:
        TestDoubleLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

TEST(Logger,TestLogging) {
    EXPECT_NO_THROW(
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%-5l] [%@ >> %!] %v");
        spdlog::set_default_logger(spdlog::stdout_logger_mt("console"));
        spdlog::set_level(spdlog::level::level_enum::trace);
    );
}

TEST(Logger,TestLoggerDefaultConstructor) {
    EXPECT_STREQ(spdlog::default_logger()->name().c_str(),TestLoggerReference::get()->data()->name().c_str());
}

TEST(Logger,TestLoggerNonExistingConstructor) {
    TestLoggerMove::get("specific_logger");
    EXPECT_TRUE(spdlog::get("specific_logger") != nullptr);
    EXPECT_STREQ(TestLoggerMove::get()->data()->name().c_str(),"specific_logger");
}

TEST(Logger,TestLoggerExistingConstructor) {
    spdlog::stdout_logger_st("console_logger");
    TestExistingLogger::get("console_logger");
    EXPECT_STREQ(TestExistingLogger::get()->data()->name().c_str(),"console_logger");
}

TEST(Logger,TestLoggerDoubleConstructor) {
    TestDoubleLogger::get("logger_console_1");
    EXPECT_STREQ(TestDoubleLogger::get()->data()->name().c_str(),"logger_console_1");
    TestDoubleLogger::get("logger_console_2");
    EXPECT_STREQ(TestDoubleLogger::get()->data()->name().c_str(),"logger_console_1");
    EXPECT_TRUE(spdlog::get("logger_console_1") != nullptr);
    EXPECT_TRUE(spdlog::get("logger_console_2") == nullptr);
}
