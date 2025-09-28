#include "fuzztest/fuzztest.h"
#include "fuzztest/googletest_fixture_adapter.h"

#include "helpers/combinators.hpp"
#include "helpers/fixtures.hpp"

using namespace fuzztest;
using namespace cecxx::benchmark;

class ComplianceTestCec2017
    : public PerFuzzTestFixtureAdapter<CecTestFixture<1e-7, cec_edition_t::cec2017, 10, 30, 50, 100>> {};

CEC_COMPLIANCE_TEST(2017, 10)
CEC_COMPLIANCE_TEST(2017, 30)
CEC_COMPLIANCE_TEST(2017, 50)
CEC_COMPLIANCE_TEST(2017, 100)
