cmake_minimum_required(VERSION 3.20)
project(missions CXX)

# --- clangd: emit compile_commands.json so the editor sees real flags ---
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- C++23 (for std::println and friends) ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Default to a Debug build, matching the Makefile's default ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# --- Warnings everywhere ---
add_compile_options(-Wall -Wextra)

# --- Per-config flags, set explicitly to mirror the Makefile exactly ---
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g -fno-omit-frame-pointer -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -DNDEBUG -DRELEASE")

# --- Apple Silicon arch flags (Linux/g++ path stays flagless, as before) ---
if(APPLE)
    add_compile_options(-march=native -mcpu=apple-m4)
endif()

# --- Shared helper code: compiled once, linked into every mission ---
file(GLOB PLIB_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/plib/*.cpp)
add_library(plib STATIC ${PLIB_SOURCES})
target_include_directories(plib PUBLIC ${CMAKE_SOURCE_DIR})

# --- One executable per missionNN.cpp ---
file(GLOB MISSION_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/mission*.cpp)
foreach(src ${MISSION_SOURCES})
    get_filename_component(name ${src} NAME_WE)   # e.g. mission01
    add_executable(${name} ${src})
    target_link_libraries(${name} PRIVATE plib)
endforeach()

# --- Convenience run / gdb targets: choose one with -DMISSION=NN ---
set(MISSION "" CACHE STRING "Mission number used by the run and gdb targets")
if(MISSION AND TARGET mission${MISSION})
    add_custom_target(run
        COMMAND $<TARGET_FILE:mission${MISSION}>
        DEPENDS mission${MISSION}
        USES_TERMINAL)
    add_custom_target(gdb
        COMMAND gdb -tui $<TARGET_FILE:mission${MISSION}>
        DEPENDS mission${MISSION}
        USES_TERMINAL)
endif()
