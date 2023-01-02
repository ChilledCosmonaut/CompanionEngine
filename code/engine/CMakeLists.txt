cmake_minimum_required(VERSION 3.18)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.h")
file(GLOB_RECURSE PRIVATE_HEADER_LIST CONFIGURE_DEPENDS "src/**.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/**.cpp")

set(ENGINE_NAME Engine)

set(GENERATED_INCLUDE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/generated")

# Generated sources
set(GENERATED_SOURCES
        Assets.h)

# Place them in a path under the cmake directory
list(TRANSFORM GENERATED_SOURCES PREPEND "${GENERATED_INCLUDE_ROOT}/")

# If we don't set those as "generated", CMAKE will throw an error.
# That's because they're referenced as sources for the executable and
# they don't already exist. They'll be generated later on.
set_source_files_properties(${GENERATED_SOURCES} GENERATED)

add_library(${ENGINE_NAME} ${HEADER_LIST} ${PRIVATE_HEADER_LIST} ${SOURCE_LIST} ${GENERATED_SOURCES})

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)
set_target_properties(${ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${ENGINE_NAME} PUBLIC glad soloud ${CONAN_LIBS})

target_include_directories(${ENGINE_NAME} PUBLIC include/ "${GENERATED_INCLUDE_ROOT}")

# Add any files you want to check for changes to trigger the python generation
set(PYTHON_GENERATORS
        generate_sources.py
        codeGenerators/__init__.py
        codeGenerators/cppbuilder.py
        codeGenerators/enumScanner.py)

#set(PYTHONPATH "${PYTHONPATH} ${GENERATED_INCLUDE_ROOT}")

# Make sure that you set the Python_ROOT_DIR environment variable to
# ensure that the desired interpreter is detected!
find_package(Python3 COMPONENTS Interpreter)
if (NOT ${Python3_FOUND})
    message(FATAL_ERROR "Python is needed to generate sources.")
endif ()

set(GENERATE_COMMAND
        "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/generate_sources.py"
        "${GENERATED_INCLUDE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_command(
        COMMAND ${GENERATE_COMMAND}

        # Command will be triggered if any of these are modified!
        DEPENDS ${PYTHON_GENERATORS}

        # Command will be triggered if any of these are missing!
        OUTPUT ${GENERATED_SOURCES}
)

install(CODE "execute_process(COMMAND ${GENERATE_COMMAND})")