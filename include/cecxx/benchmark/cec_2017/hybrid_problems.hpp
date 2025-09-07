#pragma once

#include <cecxx/benchmark/cec_2017/basic_problems.hpp>
#include <cecxx/benchmark/detail/problem_invokers/hybrid_problem_invoker.hpp>

namespace cecxx::benchmark::cec_2017 {

const auto hybrid_1 = detail::hybrid_problem_invoker{std::tuple{
                                                         cecxx::benchmark::detail::shift{},
                                                         cecxx::benchmark::detail::rotation{},
                                                         cecxx::benchmark::detail::shuffle{},

                                                     },
                                                     std::tuple{basic::zakharov, basic::rosenbrock, basic::rastrigin},
                                                     {0.2, 0.4, 0.4}};

const auto hybrid_2 = detail::hybrid_problem_invoker{std::tuple{
                                                         cecxx::benchmark::detail::shift{},
                                                         cecxx::benchmark::detail::rotation{},
                                                         cecxx::benchmark::detail::shuffle{},
                                                     },
                                                     std::tuple{basic::ellips, basic::schwefel, basic::bent_cigar},
                                                     {0.3, 0.3, 0.4}};

const auto hybrid_3
    = detail::hybrid_problem_invoker{std::tuple{
                                         cecxx::benchmark::detail::shift{},
                                         cecxx::benchmark::detail::rotation{},
                                         cecxx::benchmark::detail::shuffle{},
                                     },
                                     std::tuple{basic::bent_cigar, basic::rosenbrock, basic::bi_rastrigin},
                                     {0.3, 0.3, 0.4}};

const auto hybrid_4 = detail::hybrid_problem_invoker{
    std::tuple{
        cecxx::benchmark::detail::shift{},
        cecxx::benchmark::detail::rotation{},
        cecxx::benchmark::detail::shuffle{},
    },
    std::tuple{basic::ellips, basic::ackley, detail::needs_input_before_affine_trans{basic::schaffer},
               basic::rastrigin},
    {0.2, 0.2, 0.2, 0.4}};

const auto hybrid_5
    = detail::hybrid_problem_invoker{std::tuple{
                                         cecxx::benchmark::detail::shift{},
                                         cecxx::benchmark::detail::rotation{},
                                         cecxx::benchmark::detail::shuffle{},
                                     },
                                     std::tuple{basic::bent_cigar, basic::hgbat, basic::rastrigin, basic::rosenbrock},
                                     {0.2, 0.2, 0.3, 0.3}};

const auto hybrid_6
    = detail::hybrid_problem_invoker{std::tuple{
                                         cecxx::benchmark::detail::shift{},
                                         cecxx::benchmark::detail::rotation{},
                                         cecxx::benchmark::detail::shuffle{},
                                     },

                                     std::tuple{basic::escaffer, basic::hgbat, basic::rosenbrock, basic::schwefel},
                                     {0.2, 0.2, 0.3, 0.3}};

const auto hybrid_7 = detail::hybrid_problem_invoker{
    std::tuple{
        cecxx::benchmark::detail::shift{},
        cecxx::benchmark::detail::rotation{},
        cecxx::benchmark::detail::shuffle{},
    },

    std::tuple{basic::katsuura, basic::ackley, basic::grie_rosen, basic::schwefel, basic::rastrigin},
    {0.1, 0.2, 0.2, 0.2, 0.3}};

const auto hybrid_8 = detail::hybrid_problem_invoker{
    std::tuple{
        cecxx::benchmark::detail::shift{},
        cecxx::benchmark::detail::rotation{},
        cecxx::benchmark::detail::shuffle{},
    },

    std::tuple{basic::ellips, basic::ackley, basic::rastrigin, basic::hgbat, basic::discus},
    {0.2, 0.2, 0.2, 0.2, 0.2}};

const auto hybrid_9 = detail::hybrid_problem_invoker{
    std::tuple{
        cecxx::benchmark::detail::shift{},
        cecxx::benchmark::detail::rotation{},
        cecxx::benchmark::detail::shuffle{},
    },

    std::tuple{basic::bent_cigar, basic::rastrigin, basic::grie_rosen, basic::weierstrass, basic::escaffer},
    {0.2, 0.2, 0.2, 0.2, 0.2}};

const auto hybrid_10 = detail::hybrid_problem_invoker{
    std::tuple{
        cecxx::benchmark::detail::shift{},
        cecxx::benchmark::detail::rotation{},
        cecxx::benchmark::detail::shuffle{},
    },

    std::tuple{basic::hgbat, basic::katsuura, basic::ackley, basic::rastrigin, basic::schwefel, basic::schaffer},
    {0.1, 0.1, 0.2, 0.2, 0.2, 0.2}};

} // namespace cecxx::benchmark::cec_2017
