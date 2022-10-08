set(target stm_pod)
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB code "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${target} ${headers} ${code})
target_include_directories(${target}
    INTERFACE
    "${CMAKE_SOURCE_DIR}/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(${target}
    state_machine
    data
    hyped_utils 
)