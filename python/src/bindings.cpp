#include "cecxx/detail/benchmark/evaluator/types.hpp"
#include "nanobind/ndarray.h"
#include <cecxx/benchmark/evaluator.hpp>
#include <cecxx/mdspan.hpp>
#include <cstdint>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using namespace cecxx::benchmark;

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

auto evaluate_cec(uint16_t edition, problem_number_t number, dimension_t dimension,
                  nb::ndarray<double, nanobind::c_contig> &input) {
    const auto cec = evaluator(to_cec_edition(edition), std::vector{dimension});
    const auto mat = cecxx::mdspan{input.data(), dimension, input.shape(1)};
    const auto cec_rv = cec(number, mat);
    return nb::cast(cec_rv);
}

NB_MODULE(bindings, m) {
    m.doc() = "cecxx bindings";
    m.def(
        "cec", &evaluate_cec, "edition"_a, "number"_a, "dimension"_a, "input"_a,
        "Binding for the C++ cecxx evaluator. When using this, the input should be a row-major numpy array with shape "
        "(dimension, n_samples) - opposite to using the public API");
}
