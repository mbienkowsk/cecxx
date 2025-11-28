cmake_minimum_required(VERSION 3.19)
set(PROJECT_VER 0.1.0)

project(cecxx
  VERSION ${PROJECT_VER}
  DESCRIPTION "An implementation of CECs benchmarks in C++23"
  LANGUAGES CXX
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(Package)
include(ProjectConfig)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(HEADER_DIR ${ROOT_DIR}/include)
set(SOURCE_DIR ${ROOT_DIR}/src)

file(
  GLOB_RECURSE
  HEADERS
  CONFIGURE_DEPENDS
  ${HEADER_DIR}/*.hpp
  ${HEADER_DIR}/**/*.hpp
)

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  ${SOURCE_DIR}/*.cpp
  ${SOURCE_DIR}/**/*.cpp
  ${SOURCE_DIR}/*.hpp
  ${SOURCE_DIR}/**/*.hpp
)

if (BUILD_SHARED_LIBS)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

add_library(cecxx)
target_sources(cecxx PRIVATE ${SOURCES})
target_sources(cecxx PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES ${HEADERS}
)
target_compile_options(cecxx PRIVATE ${COMPILE_FLAGS})
target_compile_features(cecxx PRIVATE cxx_std_23)
set_target_properties(cecxx PROPERTIES 
  ARCHIVE_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)

configure_file(defaults.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/cecxx/detail/benchmark/evaluator/defaults.hpp)
generate_export_header(cecxx)

if (WITH_EXAMPLES)
  add_subdirectory(example)
endif()

if (WITH_BENCHMARKS)
  add_subdirectory(benchmark)
endif()

if (WITH_UNIT_TESTS OR WITH_COMPLIANCE_TESTS)
  if (WITH_COMPLIANCE_TESTS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_subdirectory(third-party/fuzztest)
  endif()
  add_subdirectory(test)
endif()

if (WITH_PYTHON_BINDINGS)
  add_subdirectory(python)
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cecxx.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/cecxx.pc
  @ONLY
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/cecxx.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/cecxx-config-version.cmake"
  VERSION ${PROJECT_VER}
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cecxx-config-version.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cecxx-config.cmake
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cecxx
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CECXX_BENCHMARK_DATA_STORAGE} FILES_MATCHING PATTERN "*.zip")

install(CODE
  "execute_process(COMMAND unzip -qu \"${CECXX_BENCHMARK_DATA_STORAGE}/*.zip\" -d ${CECXX_BENCHMARK_DATA_STORAGE})"
)


install(TARGETS cecxx
  EXPORT cecxxTargets
  FILE_SET HEADERS
)

install(EXPORT cecxxTargets
  NAMESPACE cecxx::
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cecxx
)
