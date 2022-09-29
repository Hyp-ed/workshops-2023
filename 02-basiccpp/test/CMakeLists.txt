set(target hyped_test)
file(GLOB code "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${target} ${code})
target_include_directories(${target}
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(${target}
    GTest::gtest_main
    workshop
)
gtest_discover_tests(${target})