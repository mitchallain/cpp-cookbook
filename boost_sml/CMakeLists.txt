cmake_minimum_required(VERSION 3.10)
project(cmake_project)

find_package(Boost 1.65.1 REQUIRED)
IF (Boost_FOUND)
  message(STATUS "BOOST FOUND !")
ELSE()
  message(STATUS "BOOST NOT Found !")
endif()

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
target_compile_options(${PROJECT_NAME} PRIVATE ${TARGET_CXX_FLAGS})
target_include_directories(${PROJECT_NAME}
  PRIVATE
  include
)

# boost > 1.72 has a headers alias
# target_link_libraries(${PROJECT_NAME}
#   PRIVATE
#   Boost::headers
# )

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED TRUE
             CXX_EXTENSIONS FALSE
)
