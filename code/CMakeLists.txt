cmake_minimum_required(VERSION 3.21)
project(code)

set(CONAN_DISABLE_CHECK_COMPILER true)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(externalCode/glad)
add_subdirectory(externalCode/glfw)
add_subdirectory(externalCode/glm)
add_subdirectory(externalCode/assimp)
add_subdirectory(externalCode/soloud)
add_subdirectory(engine)
add_subdirectory(game)


