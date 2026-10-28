cmake_minimum_required(VERSION 3.16)
project(MatrixCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/permissive-)
endif()

# Option to force downloading wxWidgets via FetchContent
option(WX_FETCH_CONTENT "Force downloading wxWidgets via FetchContent instead of searching system" OFF)

# Check if wxWidgets is already available locally/installed (unless forced to fetch)
if(NOT WX_FETCH_CONTENT)
    find_package(wxWidgets COMPONENTS core base adv QUIET)
endif()

if(wxWidgets_FOUND)
    message(STATUS "--> Using system/installed wxWidgets")
else()
    message(STATUS "--> wxWidgets not found (or WX_FETCH_CONTENT=ON). Fetching wxWidgets from GitHub via FetchContent...")
    
    # Configure wxWidgets build options to speed up compilation
    set(wxBUILD_SHARED OFF CACHE BOOL "Build wxWidgets as static libraries")
    set(wxBUILD_SAMPLES OFF CACHE BOOL "Do not build wxWidgets samples")
    set(wxBUILD_TESTS OFF CACHE BOOL "Do not build wxWidgets tests")
    set(wxBUILD_DEMOS OFF CACHE BOOL "Do not build wxWidgets demos")
    
    include(FetchContent)
    FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG        v3.2.6
        GIT_SHALLOW    ON
    )
    FetchContent_MakeAvailable(wxWidgets)
endif()

# Source files
set(SOURCES
    src/App.cpp
    src/MainFrame.cpp
    src/MatrixEquations.cpp
)

set(HEADERS
    include/App.h
    include/MainFrame.h
    include/MatrixEquations.h
    include/Globals.h
)

# GUI Target
add_executable(MatrixCalc WIN32 ${SOURCES} ${HEADERS})
target_include_directories(MatrixCalc PRIVATE include)

# Link against wxWidgets (modern targets or legacy use file)
if(TARGET wx::core)
    target_link_libraries(MatrixCalc PRIVATE wx::core wx::adv)
elseif(TARGET wxWidgets::wxWidgets)
    target_link_libraries(MatrixCalc PRIVATE wxWidgets::wxWidgets)
else()
    include(${wxWidgets_USE_FILE})
    target_link_libraries(MatrixCalc PRIVATE ${wxWidgets_LIBRARIES})
endif()

# Copy icons to output directory
add_custom_command(TARGET MatrixCalc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/icons
    $<TARGET_FILE_DIR:MatrixCalc>/icons
)

# Optional CLI Target (Legacy console version)
add_executable(MatrixCalcCLI
    cli_legacy/ConsoleMenu.cpp
    cli_legacy/MatrixCalc_Equations.h
)
target_include_directories(MatrixCalcCLI PRIVATE cli_legacy)
