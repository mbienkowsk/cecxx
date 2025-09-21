#pragma once

#include <cecxx/detail/benchmark/evaluator/context.hpp>
#include <cecxx/detail/benchmark/evaluator/types.hpp>

namespace cecxx::benchmark::cec_2013 {

auto evaluate(detail::problem_context_view_t ctx, const problem_number_t fn, std::span<const double> input) -> double;

} // namespace cecxx::benchmark::cec_2013
