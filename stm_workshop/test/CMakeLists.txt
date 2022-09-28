enable_testing()

# -------------------------------------------------- #
# BUILD TEST RUNNER                                  #
# -------------------------------------------------- #

# find test sources
file(GLOB_RECURSE test_sources "*.test.cpp")

# make target
set(test_target "testrunner")
set(TEST_BINARY "${CMAKE_BINARY_DIR}/test/testrunner")
add_executable(${test_target} EXCLUDE_FROM_ALL ${test_sources})
add_dependencies(${test_target} googletest)

# include and link
include_directories(
    ${GTEST_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/test
    ${CMAKE_SOURCE_DIR}/lib
)
target_link_libraries(${test_target}
    data
    state_machine
    hyped_utils
    pthread
    gtest
)

add_custom_target("${test_target}-format"
    COMMAND clang-format -i -style=file ${test_sources}
)
add_dependencies(${test_target} "${test_target}-format")

add_custom_target(test
    COMMAND ${TEST_BINARY}
    DEPENDS testrunner  
)
