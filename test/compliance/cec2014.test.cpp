// clang-format off
#include "gtest/gtest.h"
#include "fuzztest/fuzztest.h"
#include "fuzztest/googletest_fixture_adapter.h"
// clang-format on

#include "helpers/combinators.hpp"
#include "helpers/fixtures.hpp"

using namespace fuzztest;
using namespace cecxx::benchmark;

class Cec2014ComplianceTest
    : public PerFuzzTestFixtureAdapter<CecTestFixture<1e-7, cec_edition_t::cec2014, 10, 30, 50, 100>> {};

FUZZ_TEST_F_NAMED(Cec2014ComplianceTest, 10, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(10), InCecProblemRange(cec_edition_t::cec2014));

FUZZ_TEST_F_NAMED(Cec2014ComplianceTest, 30, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(30), InCecProblemRange(cec_edition_t::cec2014));

FUZZ_TEST_F_NAMED(Cec2014ComplianceTest, 50, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(50), InCecProblemRange(cec_edition_t::cec2014));

FUZZ_TEST_F_NAMED(Cec2014ComplianceTest, 100, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(100), InCecProblemRange(cec_edition_t::cec2014));
