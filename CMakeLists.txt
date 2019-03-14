cmake_minimum_required(VERSION 3.02)
project(fsblock)

set(BINARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(CMAKE_CURRENT_BINARY_DIR ${BINARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIRECTORY})

add_subdirectory(3rdParty EXCLUDE_FROM_ALL)

if (WIN32)
    set(PLATFORM_SRCS "src/getopt.c")
endif()

add_executable(fsblock "src/main.cpp" ${PLATFORM_SRCS})
target_link_libraries(fsblock sfw_lib)

if (MSVC)
    target_compile_options(fsblock PRIVATE "/ZI")
endif()