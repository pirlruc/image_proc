#include <improc/infrastructure/benchmark.h>

improc::Benchmark::Benchmark(std::shared_ptr<spdlog::logger>&& benchmark_logger) 
: LoggerSingleton(std::move(benchmark_logger)) {}

// std::shared_ptr<improc::Benchmark> improc::Benchmark::get_benchmark( std::string        benchmark_name
//                                                                    , const std::string& benchmark_csv_filepath )
// {
//     #ifdef WITH_DEBUG
//     spdlog::trace( "[{}:{}:{}] Obtaining benchmark {}..."
//                  , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
//                  , benchmark_name );
//     #endif    

//     const std::string kBenchmarkName   {"benchmark_logger"};
//     const std::string kTextOnlyPattern {"%v"};
//     if (benchmark_ == nullptr)
//     {
//         std::shared_ptr<spdlog::logger> benchmark_logger {};
//         if (benchmark_name.empty() == true)
//         {
//             benchmark_name = std::move(kBenchmarkName);
//         }

//         if (benchmark_csv_filepath.empty() == true)
//         {
//             #ifdef WITH_DEBUG
//             spdlog::debug( "[{}:{}:{}] Defining benchmark on console..."
//                         , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
//             #endif
//             benchmark_logger = spdlog::stdout_logger_mt(std::move(benchmark_name));    
//         }
//         else
//         {
//             #ifdef WITH_DEBUG
//             spdlog::debug( "[{}:{}:{}] Defining benchmark on file {}..."
//                         , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__
//                         , benchmark_csv_filepath );
//             #endif
//             benchmark_logger = spdlog::basic_logger_mt(std::move(benchmark_name), std::move(benchmark_csv_filepath));
//         }
//         benchmark_logger->set_level(spdlog::level::level_enum::critical);
//         benchmark_logger->set_pattern(std::move(kTextOnlyPattern));
//         benchmark_ = std::shared_ptr<Benchmark>(new Benchmark(std::move(benchmark_logger)));
//     }
//     return benchmark_;
// }

void improc::Benchmark::AddFieldsToLine() {}

template<typename arg, typename ... args>
void improc::Benchmark::AddFieldsToLine(arg field_1, args ... field_n)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Adding field to line..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif  
    this->line_msg_ += fmt::format(";{}",field_1);
    this->AddFieldsToLine(field_n ...);
}

void improc::Benchmark::WriteFields() 
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Writing fields on benchmark..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif    
    this->WriteLine();
}

template<typename arg, typename ... args>
void improc::Benchmark::WriteFields(arg field_1, args ... field_n)
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Write field on benchmark..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif  
    this->line_msg_ += fmt::format(";{}",field_1);
    this->WriteFields(field_n ...);
}

void improc::Benchmark::WriteLine()
{
    #ifdef WITH_DEBUG
    spdlog::trace( "[{}:{}:{}] Writing line on benchmark..."
                 , SPDLOG_FUNCTION,File(__FILE__).get_filename(),__LINE__ );
    #endif  
    
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
