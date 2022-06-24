cmake_minimum_required(VERSION 3.21)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externalCode/glad)
add_subdirectory(externalCode/glfw)
add_subdirectory(externalCode/glm)
add_subdirectory(externalCode/assimp)
add_subdirectory(externalCode/soloud)

set(CMAKE_HOST_SYSTEM "Windows-10.0.19043")
set(CMAKE_HOST_SYSTEM_NAME "Windows")
set(CMAKE_HOST_SYSTEM_VERSION "10.0.19043")
set(CMAKE_HOST_SYSTEM_PROCESSOR "AMD64")



set(CMAKE_SYSTEM "Windows-10.0.19043")
set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_VERSION "10.0.19043")
set(CMAKE_SYSTEM_PROCESSOR "AMD64")

set(CMAKE_CROSSCOMPILING "FALSE")

set(CMAKE_SYSTEM_LOADED 1)

set(PHYSX_ROOT_DIR externalCode/PhysX/physx)
add_subdirectory(externalCode/PhysX)
add_subdirectory(engine)
add_subdirectory(game)


