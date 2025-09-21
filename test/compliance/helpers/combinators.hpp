#pragma once

#include <type_traits>
#include <vector>

#include "cecxx/benchmark/types.hpp"
#include "fuzztest/fuzztest.h"

template <typename T>
using RngType = std::result_of_t<decltype (&fuzztest::InRange<T>)(T, T)>;

template <typename T = double>
auto BoundedVectorOf(RngType<T> rng = fuzztest::InRange(-100.0, 100.0)) {
    return fuzztest::ContainerOf<std::vector<T>>(std::forward<decltype(rng)>(rng));
}

inline auto InCecProblemRange(cecxx::benchmark::cec_edition_t edition) {
    using namespace cecxx::benchmark;
    using enum cec_edition_t;
    switch (edition) {
        case cec2013:
            return fuzztest::Filter([](int x) { return x != 31; }, fuzztest::InRange(1, 28));
        case cec2014:
            return fuzztest::Filter([](int x) { return x != 31; }, fuzztest::InRange(1, 30));
        case cec2017: {
            return fuzztest::Filter([](int x) { return x != 31; }, fuzztest::InRange(1, 30));
        }
    }
}
