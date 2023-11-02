cmake_minimum_required(VERSION 3.10)
project(spdlog_example)

## BUILD TYPES
## Release: -O3 -DNDEBUG
## Debug: -g
## RelWithDebInfo: -O2 -g -DNDEBUG
## MinSizeRel: -Os -DNDEBUG

# allow user to specify build type on command line, like
# > cmake .. -DCMAKE_BUILD_TYPE=Debug
# but default to RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

## TARGET CXX FLAGS
# Combine additional flags with existing flags in semicolon separated list
# try: `man gcc | less -cFRSX -p "Wfatal"`
# -Wfatal-errors - abort compilation at first error
# -Wall - all warnings "that some users consider questionable"
# -Wshadow - declaration shadows another variable
# -Wextra - extra warnings not enabled by Wall
# -Wpedantic - strict ISO C++
# -fPIC - produces position-independent code, suitable for dynamic linking
set(TARGET_CXX_FLAGS "-Wfatal-errors -Wall -Wshadow -Wextra -Wpedantic -fPIC")
string(REPLACE " " ";" TARGET_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TARGET_CXX_FLAGS}")

# generate build/compile_commands.json for static analysis
# note this may need to be symlinked to the project root for some tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# collect all source files into SOURCES
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# set compiler flags for the target
target_compile_options(${PROJECT_NAME} PRIVATE ${TARGET_CXX_FLAGS})

# add include directory for target
target_include_directories(${PROJECT_NAME} PRIVATE include)

# for most projects CMake 3.1+, this is the preferred way to set C++ standard
# https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED TRUE
             CXX_EXTENSIONS FALSE)

# CMake also supports the notion of compile features and
# compile "meta features" in CMake 3.8+ to set the C++ standard
# using "meta features" of the form cxx_std_YY
# https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
message(STATUS "Supported compile features = ${CMAKE_CXX_COMPILE_FEATURES}")
# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
