#include "fuzztest/fuzztest.h"
#include "fuzztest/googletest_fixture_adapter.h"

#include "helpers/combinators.hpp"
#include "helpers/fixtures.hpp"

using namespace fuzztest;
using namespace cecxx::benchmark;

class ComplianceTestCec2014
    : public PerFuzzTestFixtureAdapter<CecTestFixture<1e-7, cec_edition_t::cec2014, 10, 30, 50, 100>> {};

CEC_COMPLIANCE_TEST(2014, 10)
CEC_COMPLIANCE_TEST(2014, 30)
CEC_COMPLIANCE_TEST(2014, 50)
CEC_COMPLIANCE_TEST(2014, 100)
