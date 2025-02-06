cmake_minimum_required(VERSION 3.29)
project(sigma LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add engine cmake projects
add_subdirectory(inc/sigma)

# Compiles all C and CPP files on src folder
# To compile the game remember to set the generator to "Visual Studio 17 2022" and the compiler to the MSVC
# Ninja also works as generator but I prefer if we use Visual Studio because they may ask for an sln file in game -x
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.hpp"
        "src/*.c"
        "src/*.h"
)

add_executable(game src/main.cpp ${SRC})

# Adds sigma engine static library
target_link_libraries(game PRIVATE sigma)

# Copy res folder to build directory
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/Debug/assets)

# Copy FMOD dlls to build directory
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/inc/sigma/engine/lib/fmodL.dll ${CMAKE_BINARY_DIR}/)
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/inc/sigma/engine/lib/fmodstudioL.dll ${CMAKE_BINARY_DIR}/)

# Compile commands .json
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR})
