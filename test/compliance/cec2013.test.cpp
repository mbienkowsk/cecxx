#include "fuzztest/fuzztest.h"
#include "fuzztest/googletest_fixture_adapter.h"

#include "helpers/combinators.hpp"
#include "helpers/fixtures.hpp"

using namespace fuzztest;
using namespace cecxx::benchmark;

class Cec2013ComplianceTest : public PerFuzzTestFixtureAdapter<
                                  CecTestFixture<1e-7, cec_edition_t::cec2013, 2, 10, 20, 30, 50, 60, 80, 90, 100>> {};

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 2, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(2), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 10, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(10), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 20, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(20), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 30, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(30), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 50, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(50), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 60, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(60), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 80, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(80), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 90, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(90), InCecProblemRange(cec_edition_t::cec2013));

FUZZ_TEST_F_NAMED(Cec2013ComplianceTest, 100, CecTestFixture::evaluate)
    .WithDomains(BoundedVectorOf().WithSize(100), InCecProblemRange(cec_edition_t::cec2013));
