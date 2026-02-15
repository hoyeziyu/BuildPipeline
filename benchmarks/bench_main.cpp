#include <benchmark/benchmark.h>
#include <greeter/Greeter.h>

static void BM_Greeter_Greet(benchmark::State& state) {
    Greeter g;
    // This loop is the core of the benchmark
    for (auto _ : state) {
        // This code gets timed
        std::string result = g.greet();
        // Prevent the result from being optimized away
        benchmark::DoNotOptimize(result);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Greeter_Greet);

// Run all benchmarks
BENCHMARK_MAIN();