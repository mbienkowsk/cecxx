#include "cecxx/detail/benchmark/evaluator/types.hpp"
#include "nanobind/ndarray.h"
#include <cecxx/benchmark/evaluator.hpp>
#include <cecxx/mdspan.hpp>
#include <cstdint>
#include <cstdlib>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <print>
#include <ranges>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using namespace cecxx::benchmark;
namespace rn = std::ranges;
namespace rv = std::ranges::views;

auto example(std::vector<dimension_t> dimensions) -> int {
    try {
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

auto to_cec_edition(uint16_t edition) -> cec_edition_t {
    switch (edition) {
        case 2013:
            return cec_edition_t::cec2013;
        case 2014:
            return cec_edition_t::cec2014;
        case 2017:
            return cec_edition_t::cec2017;
        default:
            throw std::invalid_argument("Unsupported CEC edition. CEC editions supported: 2013, 2014, 2017.");
    }
}

// Input is a row-major numpy array with shape (dimension, n_samples)
auto evaluate_cec(uint16_t edition, problem_number_t number, dimension_t dimension,
                  nb::ndarray<double, nanobind::c_contig> &input) {
    const auto cec = evaluator(to_cec_edition(edition), std::vector{dimension});
    const auto mat = cecxx::mdspan{input.data(), dimension, input.shape(1)};
    const auto cec_rv = cec(number, mat);
    return nb::cast(cec_rv);
}

NB_MODULE(bindings, m) {
    m.doc() = "cecxx bindings";
    m.def("run_example", &example, "dimensions"_a);
    m.def("cec", &evaluate_cec, "edition"_a, "number"_a, "dimension"_a, "input"_a);
}
