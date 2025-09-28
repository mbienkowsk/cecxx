#include "fuzztest/fuzztest.h"
#include "fuzztest/googletest_fixture_adapter.h"

#include "helpers/combinators.hpp"
#include "helpers/fixtures.hpp"

using namespace fuzztest;
using namespace cecxx::benchmark;

class ComplianceTestCec2013 : public PerFuzzTestFixtureAdapter<
                                  CecTestFixture<1e-7, cec_edition_t::cec2013, 2, 10, 20, 30, 50, 60, 80, 90, 100>> {};

CEC_COMPLIANCE_TEST(2013, 2)
CEC_COMPLIANCE_TEST(2013, 10)
CEC_COMPLIANCE_TEST(2013, 20)
CEC_COMPLIANCE_TEST(2013, 30)
CEC_COMPLIANCE_TEST(2013, 50)
CEC_COMPLIANCE_TEST(2013, 60)
CEC_COMPLIANCE_TEST(2013, 80)
CEC_COMPLIANCE_TEST(2013, 90)
CEC_COMPLIANCE_TEST(2013, 100)
