cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(workshop-02)

# ------------------------------------------------- #
# CONFIGURE CLANG                                   #
# ------------------------------------------------- #


set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -stdlib=libc++ -lpthread -Wall -Wextra -Wpedantic")

message("compile flags: ${CMAKE_CXX_FLAGS}")
message("link flags:    ${CMAKE_CXX_LINKER_FLAGS}")

# ------------------------------------------------- #
# GOOGLE TEST                                       #
# ------------------------------------------------- #

include(ExternalProject)

ExternalProject_Add(
    googletest
    PREFIX "lib/gtest"
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

# ------------------------------------------------- #
# BUILD SRC AND TEST                                #
# ------------------------------------------------- #

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)