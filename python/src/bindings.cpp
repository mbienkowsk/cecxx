#include <cecxx/benchmark/evaluator.hpp>
#include <cecxx/mdspan.hpp>
#include <cstdlib>
#include <nanobind/nanobind.h>
#include <print>
#include <ranges>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using namespace cecxx::benchmark;
namespace rn = std::ranges;
namespace rv = std::ranges::views;

auto example() -> int {
    try {
        const auto dimensions = std::vector{10uz, 30uz, 50uz, 100uz};

        // Create an evaluator object for the CEC2017 benchmark
        auto cec_2017 = evaluator(cec_edition_t::cec2017, dimensions);

        // Create problem grid [problem_number X dimension]
        const auto problem_grid = rv::cartesian_product(dimensions, rv::iota(1, 30));

        // Evaluate given input on each optimization problem from CEC2017/D{10, 30, 50, 100}
        for (const auto &[dim, fn] : problem_grid) {
            // Prepare input matrix [dim x 2]
            const auto input = rv::repeat(0.0) | rv::take(2 * dim) | rn::to<std::vector<double>>();
            const auto mat = cecxx::mdspan{input.data(), dim, 2};

            const auto output = cec_2017(fn, mat);
            std::println("dim = {}, fn = {}, output[0] = {}, output[1] = {}", dim, fn, output[0], output[1]);
        }
    } catch (std::exception &e) {
        std::println("Failed: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

NB_MODULE(bindings, m) {
    m.doc() = "cecxx bindings";
    m.def("run_example", &example);
}
