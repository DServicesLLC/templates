cmake_minimum_required(VERSION 3.30)

project(wxapp VERSION 1.0.0 LANGUAGES CXX C)

# Set standards
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find or fetch wxWidgets
include(FetchContent)
find_package(wxWidgets QUIET COMPONENTS core base)

if(NOT wxWidgets_FOUND)
    FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG v3.3.0
        GIT_SHALLOW TRUE
    )
    set(wxBUILD_SHARED OFF CACHE BOOL "")
    set(wxBUILD_SAMPLES OFF CACHE BOOL "")
    set(wxBUILD_TESTS OFF CACHE BOOL "")
    FetchContent_MakeAvailable(wxWidgets)
    set(WX_LIBS wx::core wx::base)
else()
    include(${wxWidgets_USE_FILE})
    set(WX_LIBS ${wxWidgets_LIBRARIES})
endif()

# Build executable
file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.c")
add_executable(${PROJECT_NAME} app.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${WX_LIBS})

if(wxWidgets_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${wxWidgets_DEFINITIONS})
endif()

# Platform settings
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
endif()
