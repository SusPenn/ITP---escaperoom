# CMakeList.txt : CMake project for EscapeRoom, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.8)
project("EscapeRoom")

# Add source to this project's executable.
add_executable(EscapeRoom "src/main.cpp") # Removed "include/EscapeRoom.hpp" since it's not necessary here

# Set C++20 as the standard for the project
set_property(TARGET EscapeRoom PROPERTY CXX_STANDARD 20)

# Specify the path to the SFML CMake modules
set(SFML_DIR "${PROJECT_SOURCE_DIR}/external/SFML")

# Find SFML components
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Include directories for this project's executable
target_include_directories(EscapeRoom PRIVATE
    "${PROJECT_SOURCE_DIR}/include" # Add your project's include directory
    "${PROJECT_SOURCE_DIR}/external/SFML/include" # SFML include directory
)

# Link SFML libraries
target_link_libraries(EscapeRoom sfml-graphics sfml-audio)

# Copy SFML DLLs to the output directory after building (only needed if using dynamic SFML libs on Windows)
add_custom_command(TARGET EscapeRoom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/external/SFML"
    $<TARGET_FILE_DIR:EscapeRoom>)

# TODO: Add tests and install targets if needed.