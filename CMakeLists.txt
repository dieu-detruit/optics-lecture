cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "/usr/bin/g++" CACHE STRING "g++ compiler" FORCE)
set(CMAKE_C_COMPILER "/usr/bin/gcc" CACHE STRING "gcc compiler" FORCE)
set(CMAKE_C_FLAG "${CMAKE_C_FLAGS} -g -O0 -fmax-errors=5 -Wfatal-erros")
set(CMAKE_CXX_FLAG "${CMAKE_C_FLAGS} -g -O0 -fmax-errors=5 -Wfatal-erros -std=c++17")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OPTICS_LECTURE LANGUAGES C CXX)

# build optics lib as subdirectory (name: optics)
add_subdirectory(external/optics)
set(optics_INCLUDE_DIRS
    external/optics/include)

# find packages and include files
find_package(Eigen3 REQUIRED)
include(external/optics/libopt.cmake)

set(COMMON_INCLUDE_DIRS
    ${EIGEN3_INCLUDE_DIRS}
    ${LIBOPT_INCLUDE_DIRS}
    )
set(COMMON_LINK_LIBRARIES
    optics
    )

### set executables
function(set_executable dirname)
    file(GLOB TEST_SOURCES ${dirname}/*.cpp)
    foreach(TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

        add_executable(${TEST_NAME} ${TEST_SOURCE})
        target_include_directories(${TEST_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
        target_link_libraries(${TEST_NAME} ${COMMON_LINK_LIBRARIES})
    endforeach()
endfunction()

set_executable(testsuite)
set_executable(lecture)
