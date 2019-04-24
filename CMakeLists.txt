cmake_minimum_required (VERSION 3.5)

project(lfbg VERSION 0.1.0 DESCRIPTION "graphics library for my old dos codes that used VESA modes")

option(BUILD_EXAMPLES "Build the example programs" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set( CMAKE_CXX_STANDARD 11 )
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "/DEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /arch")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
endif()

# glfw
set( GLFW_BUILD_DOCS OFF CACHE INTERNAL "" )
set( GLFW_BUILD_TESTS OFF CACHE INTERNAL "" )
set( GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "" )
add_subdirectory( deps/glfw )

# external includes
#include_directories( SYSTEM "deps/glad/include" )

file(GLOB SRC_FILES "src/*.cpp" "deps/glad/src/glad.c")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_include_directories( ${PROJECT_NAME} PUBLIC "deps/glad/include" )
target_link_libraries(${PROJECT_NAME} glfw)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
