option(WITH_COMPLIANCE_TESTS "Build compliance tests" OFF)
option(WITH_UNIT_TESTS "Build unit tests" OFF)

option(WITH_EXAMPLES "Build examples" OFF)
option(WITH_BENCHMARKS "Build benchmarks" OFF)

set(CECXX_BENCHMARK_DATA_STORAGE "/var/lib/cecxx")
set(CECXX_TARGET_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/artifacts")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(COMPILE_FLAGS -Wall -Wpedantic -Wextra -Wconversion -Wimplicit-fallthrough -Wundef)
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 14.0)
    set(COMPILE_FLAGS ${COMPILE_FLAGS} -Wnrvo)
  endif()
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(COMPILE_FLAGS -Wall -Wextra -pedantic -Wconversion -Wundef
    -Wdeprecated -Wshadow)
endif()
