add_compile_definitions(DATA_STORAGE_PATH="${CMAKE_SOURCE_DIR}/data")

set(EVAL_EACH_PROBLEM_EXAMPLE "evaluate-each-problem")

add_executable(${EVAL_EACH_PROBLEM_EXAMPLE} evaluate_each_problem.cpp )
target_link_libraries(${EVAL_EACH_PROBLEM_EXAMPLE} PRIVATE cecxx)
set_target_properties(
  ${EVAL_EACH_PROBLEM_EXAMPLE} PROPERTIES CXX_STANDARD 23
  ARCHIVE_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/bin"
)
target_compile_options(${EVAL_EACH_PROBLEM_EXAMPLE} PRIVATE -Wall -Wextra -Wpedantic -O3)



set(EVAL_SEP_PROBLEM_EXAMPLE "evaluate-separate-problem")
add_executable(${EVAL_SEP_PROBLEM_EXAMPLE} evaluate_separate_problem.cpp "${CMAKE_SOURCE_DIR}/test/compliance/oracle/cec2017.cpp")
target_link_libraries(${EVAL_SEP_PROBLEM_EXAMPLE} PRIVATE cecxx)
set_target_properties(
  ${EVAL_SEP_PROBLEM_EXAMPLE} PROPERTIES CXX_STANDARD 23
  ARCHIVE_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CECXX_TARGET_OUTPUT_DIR}/bin"
)
target_compile_options(${EVAL_SEP_PROBLEM_EXAMPLE} PRIVATE -Wall -Wextra -Wpedantic -O3)

