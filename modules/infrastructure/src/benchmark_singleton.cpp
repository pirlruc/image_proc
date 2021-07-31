#include <improc/infrastructure/benchmark_singleton.h>

template <typename type>
improc::BenchmarkSingleton<type>::BenchmarkSingleton(std::shared_ptr<spdlog::logger>&& benchmark_logger) 
: LoggerSingleton<type>(std::move(benchmark_logger)) 
{
    SPDLOG_LOGGER_CALL(improc::InfrastructureLogger::get()->data(),spdlog::level::trace,"Creating benchmark logger...");
    this->data()->set_level(spdlog::level::critical);
    this->data()->set_pattern("%n;%v");
}

template <typename type>
improc::BenchmarkSingleton<type>::BenchmarkSingleton(const std::shared_ptr<spdlog::logger>& benchmark_logger) 
: LoggerSingleton<type>(std::move(benchmark_logger)) 
{
    SPDLOG_LOGGER_CALL(improc::InfrastructureLogger::get()->data(),spdlog::level::trace,"Creating benchmark logger...");
    this->data()->set_level(spdlog::level::critical);
    this->data()->set_pattern("%n;%v");
}

template <typename type>
void improc::BenchmarkSingleton<type>::AddFieldsToLine() {}

template <typename type>
template<typename arg, typename ... args>
void improc::BenchmarkSingleton<type>::AddFieldsToLine(arg field_1, args ... field_n)
{
    SPDLOG_LOGGER_CALL(improc::InfrastructureLogger::get()->data(),spdlog::level::trace,"Adding field to line...");
    this->line_msg_ += fmt::format(";{}",field_1);
    this->AddFieldsToLine(field_n ...);
}

template <typename type>
void improc::BenchmarkSingleton<type>::WriteFields() 
{
    SPDLOG_LOGGER_CALL(improc::InfrastructureLogger::get()->data(),spdlog::level::trace,"Writing fields on benchmark...");
    this->WriteLine();
}

template <typename type>
template<typename arg, typename ... args>
void improc::BenchmarkSingleton<type>::WriteFields(arg field_1, args ... field_n)
{
    SPDLOG_LOGGER_CALL(improc::InfrastructureLogger::get()->data(),spdlog::level::trace,"Formatting fields to write on benchmark...");
    this->line_msg_ += fmt::format(";{}",field_1);
    this->WriteFields(field_n ...);
}

template <typename type>
void improc::BenchmarkSingleton<type>::WriteLine()
{
    SPDLOG_LOGGER_CALL(improc::InfrastructureLogger::get()->data(),spdlog::level::trace,"Writing line on benchmark...");
    if (this->line_msg_.size() > 0)
    {
        // Remove first character since there is an additional ";" at the beginning
        this->data()->critical(this->line_msg_.substr(1,std::string::npos));
    }
    else
    {
        this->data()->critical(this->line_msg_);
    }
    this->line_msg_.clear();
}
