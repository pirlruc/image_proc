#include <gtest/gtest.h>

#define WITH_DEBUG
#include <improc/infrastructure/file.h>
#include <improc/infrastructure/benchmark.h>
#include <benchmark.cpp>

// TEST(Benchmark,TestBenchmarkDefaultConstructor) {
//     improc::Benchmark::get_benchmark();
//     EXPECT_TRUE(spdlog::get("benchmark_logger") != nullptr);
// }

// TEST(Benchmark,TestBenchmarkConsoleConstructor) {
//     improc::Benchmark::get_benchmark("benchmark_console_logger");
//     EXPECT_TRUE(spdlog::get("benchmark_console_logger") != nullptr);
// }

// TEST(Benchmark,TestBenchmarkFileConstructor) {
//     improc::Benchmark::get_benchmark("benchmark_file_logger","./benchmark_file.csv");
//     EXPECT_TRUE(spdlog::get("benchmark_file_logger") != nullptr);
//     EXPECT_TRUE(improc::File("./benchmark_file.csv").Exists());
// }

// TEST(Benchmark,TestBenchmarkDoubleConstructor) {
//     improc::Benchmark::get_benchmark("benchmark_console_1");
//     improc::Benchmark::get_benchmark("benchmark_console_2");
//     EXPECT_TRUE(spdlog::get("benchmark_console_1") != nullptr);
//     EXPECT_TRUE(spdlog::get("benchmark_console_2") == nullptr);
// }

// TEST(Benchmark,TestBenchmarkWriteEmptyLine) {
//     improc::Benchmark::get_benchmark("benchmark_file_logger","./benchmark_file.csv");
//     improc::Benchmark::get_benchmark()->WriteLine();
//     EXPECT_STREQ(improc::File::Read("./benchmark_file.csv").c_str(),"");
// }

TEST(Benchmark,TestBenchmarkWriteSameTypeFields) {
    improc::Benchmark::get_benchmark("benchmark_console_logger");
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->WriteFields(1));
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->WriteFields(1,2,3));
}

TEST(Benchmark,TestBenchmarkWriteDiffTypeFields) {
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->WriteFields(false));
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->WriteFields("test1",2,3.14));
}

TEST(Benchmark,TestBenchmarkAddSameTypeFields) {
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->AddFieldsToLine(1));
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->AddFieldsToLine(2,3,4));
    improc::Benchmark::get_benchmark()->WriteLine();
}

TEST(Benchmark,TestBenchmarkAddDiffTypeFields) {
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->AddFieldsToLine(false));
    EXPECT_NO_THROW(improc::Benchmark::get_benchmark()->AddFieldsToLine("test1",2,3.14));
    improc::Benchmark::get_benchmark()->WriteLine();
}
