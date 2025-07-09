cmake_minimum_required(VERSION 4.0.2)
project(discord_bot)

set(CMAKE_C_STANDARD 26)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler warnings:
# -Wall      : Enables most common warnings.
# -Wextra    : Enables additional warnings beyond -Wall.
# -Wpedantic : Warns on non-standard ISO behavior (can be noisy, optional).
add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

find_package(dpp REQUIRED)

if(NOT dpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
    	dpp
	GIT_REPOSITORY https://github.com/brainboxdotcc/DPP
	GIT_TAG master
    )
    FetchContent_MakeAvailable(dpp)
endif()

include_directories(
    ./include
    ./include/commands
)

# Include source files from source directory
include(source/CMakeLists.txt)

# Prepend source/ to each file in SOURCE_FILES
foreach(file ${SOURCE_FILES})
    list(APPEND SOURCES "source/${file}")
endforeach()

# Add main bot.cpp
list(APPEND SOURCES bot.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE dpp::dpp)
