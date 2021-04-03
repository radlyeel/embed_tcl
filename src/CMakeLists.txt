cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

# Handle potential Windows/Cygwin issue
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("EmbedTcl")

# Get info for Tcl
find_package(Tcl)

# Assume we found it; TODO: Handle failure to find it
include_directories(SYSTEM ${TCL_INCLUDE_PATH})

# TCL Bindings
add_library(tcl_ext SHARED
  tcl_bindings
  )
target_link_libraries(tcl_ext ${TCL_LIBRARY})

# Main program
add_executable(embedtcl
        main.c
        )
target_link_libraries(embedtcl ${TCL_LIBRARY})

# What is this for?
set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")

