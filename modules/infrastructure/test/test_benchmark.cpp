#include <gtest/gtest.h>

#include <improc/infrastructure/file.h>
#include <improc/infrastructure/benchmark_singleton.h>
#include <logger_singleton.cpp>
#include <benchmark_singleton.cpp>

#include <spdlog/sinks/basic_file_sink.h>

class TestBenchmarkReference : public improc::BenchmarkSingleton<TestBenchmarkReference>
{
    friend std::shared_ptr<TestBenchmarkReference> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkReference(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(logger) {}
};

class TestBenchmarkMove : public improc::BenchmarkSingleton<TestBenchmarkMove>
{
    friend std::shared_ptr<TestBenchmarkMove> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkMove(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkDiff : public improc::BenchmarkSingleton<TestBenchmarkDiff>
{
    friend std::shared_ptr<TestBenchmarkDiff> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkDiff(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkAddSame : public improc::BenchmarkSingleton<TestBenchmarkAddSame>
{
    friend std::shared_ptr<TestBenchmarkAddSame> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkAddSame(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkAddDiff : public improc::BenchmarkSingleton<TestBenchmarkAddDiff>
{
    friend std::shared_ptr<TestBenchmarkAddDiff> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkAddDiff(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

TEST(Benchmark,TestBenchmarkLevelAndPattern) {
    improc::File::Remove("./benchmark_1.csv");
    spdlog::basic_logger_st("benchmark1","./benchmark_1.csv");
    TestBenchmarkReference::get("benchmark1")->WriteLine();
    TestBenchmarkReference::get()->data()->flush();
    EXPECT_EQ(TestBenchmarkReference::get()->data()->level(),spdlog::level::critical);
    EXPECT_STREQ(improc::File::Read("./benchmark_1.csv").c_str(),"benchmark1;\n");
}

TEST(Benchmark,TestBenchmarkWriteSameTypeFields) {
    improc::File::Remove("./benchmark_1.csv");
    spdlog::basic_logger_st("benchmark2","./benchmark_1.csv");
    EXPECT_NO_THROW (
        TestBenchmarkMove::get("benchmark2")->WriteFields(1);
        TestBenchmarkMove::get()->WriteFields(1,2,3);
    );
    TestBenchmarkMove::get()->data()->flush();
    EXPECT_STREQ(improc::File::Read("./benchmark_1.csv").c_str(),"benchmark2;1\nbenchmark2;1;2;3\n");
}

TEST(Benchmark,TestBenchmarkWriteDiffTypeFields) {
    improc::File::Remove("./benchmark_1.csv");
    spdlog::basic_logger_st("benchmark3","./benchmark_1.csv");
    EXPECT_NO_THROW (
        TestBenchmarkDiff::get("benchmark3")->WriteFields(false);
        TestBenchmarkDiff::get()->WriteFields("test1",2,3.14);
    );
    TestBenchmarkDiff::get()->data()->flush();
    EXPECT_STREQ(improc::File::Read("./benchmark_1.csv").c_str(),"benchmark3;false\nbenchmark3;test1;2;3.14\n");
}

TEST(Benchmark,TestBenchmarkAddSameTypeFields) {
    improc::File::Remove("./benchmark_1.csv");
    spdlog::basic_logger_st("benchmark4","./benchmark_1.csv");
    EXPECT_NO_THROW (
        TestBenchmarkAddSame::get("benchmark4")->AddFieldsToLine(1);
        TestBenchmarkAddSame::get()->AddFieldsToLine(2,3,4);
        TestBenchmarkAddSame::get()->WriteLine();
    );
    TestBenchmarkAddSame::get()->data()->flush();
    EXPECT_STREQ(improc::File::Read("./benchmark_1.csv").c_str(),"benchmark4;1;2;3;4\n");
}

TEST(Benchmark,TestBenchmarkAddDiffTypeFields) {
    improc::File::Remove("./benchmark_1.csv");
    spdlog::basic_logger_st("benchmark5","./benchmark_1.csv");
    EXPECT_NO_THROW (
        TestBenchmarkAddDiff::get("benchmark5")->AddFieldsToLine(false);
        TestBenchmarkAddDiff::get()->AddFieldsToLine("test1",2,3.14);
        TestBenchmarkAddDiff::get()->WriteLine();
    );
    TestBenchmarkAddDiff::get()->data()->flush();
    EXPECT_STREQ(improc::File::Read("./benchmark_1.csv").c_str(),"benchmark5;false;test1;2;3.14\n");
}
