set(target workshop-lib)
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB code "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(${target} ${headers} ${code})
target_include_directories(${target}
    INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_custom_target("${target}-format"
    COMMAND clang-format -i -style=file ${code} ${headers}
)
add_dependencies(${target} "${target}-format")