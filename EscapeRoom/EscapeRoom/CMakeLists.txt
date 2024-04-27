cmake_minimum_required(VERSION 3.8)
project("EscapeRoom")

# Add source to this project's executable.
add_executable(EscapeRoom "src/main.cpp" "src/AudioManager.cpp")

# Set C++20 as the standard for the project
set_property(TARGET EscapeRoom PROPERTY CXX_STANDARD 20)

# Path to SFML's CMake configuration files
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/external/SFML/lib/cmake/SFML")

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
add_custom_command(TARGET EscapeRoom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/external/SFML/bin"
    $<TARGET_FILE_DIR:EscapeRoom>)

add_custom_command(TARGET EscapeRoom POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"${PROJECT_SOURCE_DIR}/assets" # Source of assets
$<TARGET_FILE_DIR:EscapeRoom>/assets) # Target directory in the build output