cmake_minimum_required(VERSION 3.8)
project("EscapeRoom")

# Add source to this project's executable.
add_executable(EscapeRoom "src/main.cpp" "src/AudioManager.cpp" "src/Intro.cpp" "src/MainMenu.cpp" "src/Button" "src/GameLoop" "src/Inventory" "src/Item" "src/Player" "src/Riddle" "src/Room" "src/Timer" "src/Visuals" "src/Outro" "src/FinalRoom" ) 

# Set C++20 as the standard for the project
set_property(TARGET EscapeRoom PROPERTY CXX_STANDARD 20)

# Path to SFML's CMake configuration files
if (WIN32)
    set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/external/SFML_WIN32/lib/cmake/SFML")
elseif (APPLE)
    set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/external/SFML_APPLE/lib")
endif()


# Find SFML components
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

# Include directories for this project's executable
target_include_directories(EscapeRoom PRIVATE
    "${PROJECT_SOURCE_DIR}/include"  # Project's include directory
    "${PROJECT_SOURCE_DIR}/external/SFML/include"  # SFML include directory
)

# Link SFML libraries
target_link_libraries(EscapeRoom sfml-graphics sfml-audio)

# Copy SFML DLLs to the output directory after building (only needed if using dynamic SFML libs on Windows)
if(WIN32)
    add_custom_command(TARGET EscapeRoom POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/external/SFML_WIN32/bin"
        $<TARGET_FILE_DIR:EscapeRoom>)
elseif(APPLE)
    add_custom_command(TARGET EscapeRoom POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/external/SFML_APPLE"
            $<TARGET_FILE_DIR:EscapeRoom>)
endif()

add_custom_command(TARGET EscapeRoom POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"${PROJECT_SOURCE_DIR}/assets" # Source of assets
$<TARGET_FILE_DIR:EscapeRoom>/assets) # Target directory in the build output