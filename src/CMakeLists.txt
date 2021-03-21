cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

# Handle potential Windows/Cygwin issue
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("EmbedTcl")

# Get info for Boost and Tcl
find_package(Boost 1.32 REQUIRED COMPONENTS program_options)
find_package(Tcl)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(SYSTEM ${TCL_INCLUDE_PATH})

add_executable(embedtcl
        main.cpp
        )
target_link_libraries(embedtcl ${Boost_LIBRARIES} ${TCL_LIBRARY})

# What is this for?
set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")

