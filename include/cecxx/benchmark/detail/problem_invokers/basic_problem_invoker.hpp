#pragma once

#include "cecxx/benchmark/types.hpp"
#include <cecxx/benchmark/detail/func_types.hpp>
#include <optional>
#include <print>
#include <ranges>
#include <utility>

#include <cecxx/benchmark/detail/problem_invokers/affine_transformations.hpp>

namespace cecxx::benchmark::detail {

template <typename EvaluationFunctionT, typename... AffineTransformationT>
struct basic_problem_invoker {
    using evaluation_function_t = EvaluationFunctionT;

    constexpr basic_problem_invoker(EvaluationFunctionT fn, affine_mask_t mask,
                                    std::tuple<AffineTransformationT...> affine_fns)
        : fn_{std::move(fn)}, mask_{mask}, trans_{affine_fns} {}

    auto operator()(std::span<const double> input, problem_context_view_t ctx,
                    std::optional<affine_mask_t> mask = {}) const -> double {
        const auto used_mask = mask.has_value() ? mask.value() : mask_;
        if constexpr (std::is_same_v<EvaluationFunctionT, contextless_eval_func>) {
            return fn_(apply_geom_fns(input, ctx, used_mask, trans_));
        } else if constexpr (std::is_same_v<EvaluationFunctionT, contextful_eval_func>) {
            return fn_(input, ctx, used_mask);
        }

        throw std::runtime_error{"Failed to identify type of function"};
    }

    EvaluationFunctionT fn_{};
    affine_mask_t mask_{};
    std::tuple<AffineTransformationT...> trans_{};
};

} // namespace cecxx::benchmark::detail
