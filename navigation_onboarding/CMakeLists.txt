cmake_minimum_required(VERSION 3.22.0)


# -------------------------------------------------- #
# LIB HELPER                                         #
# -------------------------------------------------- #
set(ALL_LIBS "navigation")
function(make_lib target, include_path)
    file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
    file(GLOB code "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    add_library(${target} STATIC ${headers} ${code})
    target_include_directories(${target}
        INTERFACE ${include_path}
    )
    set(link_libs ${ALL_LIBS})
    list(REMOVE_ITEM link_libs "${target}")
    target_link_libraries(${target} ${link_libs})
endfunction()


# -------------------------------------------------- #
# BUILD LIBS                                         #
# -------------------------------------------------- #

set(project nav_onboard)
project(${project} CXX)

set(target "nav")
add_executable(${target} ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

#add_subdirectory(navigation)
target_link_libraries(${target} navigation)