if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  cmake_minimum_required(VERSION 3.19)
  project(cecxx_bindings) # TODO: see if names can shadow
endif()

set(Python_FIND_VIRTUALENV FIRST)
set(VENV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.venv")

if (NOT DEFINED ENV{VIRTUAL_ENV} AND EXISTS "${VENV_DIR}")
  message(STATUS "Found local .venv, forcing CMake to use it.")
  set(Python_ROOT_DIR ${VENV_DIR})
else()
  message(STATUS "Looked for venv in ${VENV_DIR}, did not find it.")
endif()

find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule
)

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)


nanobind_add_module(bindings STABLE_ABI NB_STATIC src/bindings.cpp)

nanobind_add_stub(
  cecxx_bindings_stub
  MODULE bindings
  MARKER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cecxx/py.typed"
  OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/cecxx/bindings.pyi"
  PYTHON_PATH $<TARGET_FILE_DIR:bindings>
  DEPENDS bindings
)
add_custom_target(build_stubs ALL DEPENDS cecxx_bindings_stub)

target_compile_features(bindings PRIVATE cxx_std_23)
target_link_libraries(bindings PRIVATE cecxx)

install(TARGETS bindings LIBRARY DESTINATION cecxx)

# TODO: stubs
