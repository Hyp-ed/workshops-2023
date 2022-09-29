set(target "workshop-test")

file(GLOB code "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${target} ${code})
add_dependencies(${target} googletest)

add_custom_target("${target}-format"
    COMMAND clang-format -i -style=file ${code}
)
add_dependencies(${target} "${target}-format")
target_link_libraries(${target}
    gtest
    workshop-lib
)

add_custom_target(test
    COMMAND "${CMAKE_BINARY_DIR}/test/workshop-test"
    DEPENDS workshop-test
)