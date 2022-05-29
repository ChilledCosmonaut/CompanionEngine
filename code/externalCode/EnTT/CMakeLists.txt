cmake_minimum_required(VERSION 3.18)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.hpp")

set(LIBRARY_NAME EnTT)

add_library(${LIBRARY_NAME} "include/entt.hpp")

target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_17)
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIBRARY_NAME} PUBLIC include/)