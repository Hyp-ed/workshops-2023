cmake_minimum_required(VERSION 3.12.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wpedantic ")
set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -stdlib=libc++")

set(project stm_workshop)
project(${project} CXX)

include(ExternalProject)
ExternalProject_Add(
    googletest
    PREFIX "test/gtest"
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG        main
    TIMEOUT 10
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/googletest/include)
set_target_properties(googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)

ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/lib/libgtest.a)
set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION
                ${GTEST_LIBRARY_PATH} )
add_dependencies(${GTEST_LIBRARY} googletest)
set_target_properties(gtest PROPERTIES EXCLUDE_FROM_ALL TRUE)

include_directories(${GTEST_INCLUDE_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)