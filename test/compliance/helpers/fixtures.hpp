#pragma once

#include "gtest/gtest.h"

#include "cecxx/benchmark/evaluator.hpp"
#include "cecxx/detail/benchmark/evaluator/types.hpp"
#include "oracle/cec2013.h"
#include "oracle/cec2014.h"
#include "oracle/cec2017.h"

#define FUZZ_TEST_F_NAMED(fixture, test_name, func) INTERNAL_FUZZ_TEST_F(fixture, test_name, fixture, func)

inline auto get_oracle(cecxx::benchmark::cec_edition_t e) {
    using enum cecxx::benchmark::cec_edition_t;
    switch (e) {
        case cec2013:
            return oracle::cec2013::cec13_test_func;
        case cec2014:
            return oracle::cec2014::cec14_test_func;
        case cec2017:
            return oracle::cec2017::cec17_test_func;
    }
}

inline auto calculate_oracle_output(cecxx::benchmark::cec_edition_t edition, std::span<double> input,
                                    const int problem_num) -> double {
    auto output = std::array<double, 1>{};
    auto &&oracle = get_oracle(edition);
    oracle(input.data(), output.data(), input.size(), 1, problem_num);
    return output[0];
}

template <double MaxAbsoluteError, cecxx::benchmark::cec_edition_t Edition, std::size_t... Dimension>
struct CecTestFixture : public testing::Test {
    CecTestFixture() : evaluator_{cecxx::benchmark::evaluator(edition_, std::array{Dimension...}, DATA_STORAGE_PATH)} {}

    void evaluate(std::vector<double> input, const int problem_num) {
        const auto oracle_output = calculate_oracle_output(edition_, input, problem_num);
        const auto cecxx_output = evaluator_(problem_num, cecxx::mdspan{input.data(), input.size(), 1});
        EXPECT_NEAR(oracle_output, cecxx_output[0], max_abs_err_);
    }

    static constexpr double max_abs_err_{MaxAbsoluteError};
    cecxx::benchmark::cec_edition_t edition_{Edition};
    cecxx::benchmark::evaluator evaluator_;
};
