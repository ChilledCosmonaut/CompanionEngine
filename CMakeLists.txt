cmake_minimum_required(VERSION 3.21)
project(code)

set(CONAN_DISABLE_CHECK_COMPILER true)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(externalCode/glad)
add_subdirectory(externalCode/soloud)
add_subdirectory(engine)
add_subdirectory(game)


