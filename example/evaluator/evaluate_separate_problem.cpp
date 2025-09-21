#include "cecxx/mdspan.hpp"
#include <cassert>
#include <cstdlib>
#include <exception>
#include <functional>
#include <print>
#include <ranges>
#include <vector>

#include <cecxx/benchmark/evaluator.hpp>

namespace rn = std::ranges;
namespace rv = std::ranges::views;
using namespace cecxx::benchmark;

auto dummy_optimizer(cecxx::benchmark::matrix_t x0, std::function<std::vector<double>(matrix_t)> fn) -> double {
    auto result = fn(x0);
    return result[0];
}

auto main() -> int {
    try {
        constexpr auto fn_num = 3;
        constexpr auto dim{10uz};
        // Create an evaluator object for the CEC2017 benchmark for 50D
        auto cec_2017 = evaluator(cecxx::benchmark::cec_edition_t::cec2017, std::vector{dim});

        // Extract problem F3 from CEC2017/D50
        auto fn = cec_2017.extract_problem(fn_num, dim);

        // Prepare starting point for your optimization solver
        const auto data = rv::repeat(0.0) | rv::take(dim) | rn::to<std::vector<double>>();

        const auto x0 = cecxx::mdspan{data.data(), dim, 1};

        // Pass problem F3 to your optimizer together with starting point
        const auto result = dummy_optimizer(x0, fn);
        std::println("Dummy optimizer's result: {}", result);
    } catch (std::exception &e) {
        std::println("Failed: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
