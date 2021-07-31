#ifndef IMPROC_INFRASTRUCTURE_BENCHMARK_H
#define IMPROC_INFRASTRUCTURE_BENCHMARK_H

#include <improc/improc_defs.h>

#include <improc/infrastructure/file.h>
#include <improc/infrastructure/logger_singleton.h>

#ifdef WITH_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace improc {
    class IMPROC_EXPORTS Benchmark : public LoggerSingleton<Benchmark>
    {
        private:
             std::string                         line_msg_;

        public:
            Benchmark     (Benchmark& that)        = delete;
            Benchmark     (Benchmark&& that)       = delete;
            void operator=(const Benchmark& that)  = delete;
            void operator=(const Benchmark&& that) = delete;

            Benchmark(std::shared_ptr<spdlog::logger>&& benchmark_logger);

            void                                AddFieldsToLine ();
            void                                WriteFields     ();
            void                                WriteLine       ();

            template<typename arg, typename ... args>
            void                                AddFieldsToLine (arg field_1, args ... field_n);

            template<typename arg, typename ... args>
            void                                WriteFields     (arg field_1, args ... field_n);
    };
}
// namespace improc {
//     class IMPROC_EXPORTS Benchmark
//     {
//         private:
//             static std::shared_ptr<Benchmark>   benchmark_;
//             std::shared_ptr<spdlog::logger>     data_;
//             std::string                         line_msg_;

//         private:
//             Benchmark(std::shared_ptr<spdlog::logger>&& benchmark_logger);

//         public:
//             Benchmark     (Benchmark& that)        = delete;
//             Benchmark     (Benchmark&& that)       = delete;
//             void operator=(const Benchmark& that)  = delete;
//             void operator=(const Benchmark&& that) = delete;

//             static std::shared_ptr<Benchmark>   get_benchmark   ( std::string        benchmark_name         = ""
//                                                                 , const std::string& benchmark_csv_filepath = "" );

//             void                                AddFieldsToLine ();
//             void                                WriteFields     ();
//             void                                WriteLine       ();

//             template<typename arg, typename ... args>
//             void                                AddFieldsToLine (arg field_1, args ... field_n);

//             template<typename arg, typename ... args>
//             void                                WriteFields     (arg field_1, args ... field_n);
//     };

//     std::shared_ptr<Benchmark> Benchmark::benchmark_ {nullptr};
// }

#endif