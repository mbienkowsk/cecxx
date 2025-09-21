#pragma once

#include <cecxx/detail/benchmark/evaluator/context.hpp>
#include <cecxx/detail/benchmark/evaluator/types.hpp>

namespace cecxx::benchmark::detail {
template <typename EvaluationFunctionT>
struct pass_full_input_decorator {
    using evaluation_function_t = EvaluationFunctionT;
    auto operator()(std::span<const double> input, problem_context_view_t ctx,
                    std::optional<affine_mask_t> mask) const {
        return fn(input, ctx, mask);
    }

    EvaluationFunctionT fn;
};

} // namespace cecxx::benchmark::detail
