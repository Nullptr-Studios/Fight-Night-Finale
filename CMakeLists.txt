cmake_minimum_required(VERSION 3.29)
project(sigma LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_BUILD_TYPE "Debug")

message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")
message("${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    cmake_policy(SET CMP0077 NEW)
    # add_compile_options(/W4)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/LTCG")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob3 /Qfast_transcendentals /fp:fast")
    set(GLM_ENABLE_SIMD_AVX2 ON)
    set(GLM_ENABLE_FAST_MATH ON)
    set(GLM_ENABLE_LANG_EXTENSIONS ON)
endif ()

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

add_executable(game src/main.cpp ${SRC}
        src/Objects/Door.cpp
        src/Objects/Door.hpp)

target_include_directories(game PUBLIC src)

# Adds sigma engine static library
target_link_libraries(game PRIVATE sigma)

# Copy res folder to build directory
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/assets)

# Copy FMOD dlls to build directory
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_custom_command(TARGET game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/inc/sigma/engine/lib/fmodL.dll ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
    add_custom_command(TARGET game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/inc/sigma/engine/lib/fmodstudioL.dll ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
else ()
    add_custom_command(TARGET game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/inc/sigma/engine/lib/fmod.dll ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
    add_custom_command(TARGET game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/inc/sigma/engine/lib/fmodstudio.dll ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
endif ()

# Compile commands .json
#add_custom_command(TARGET game POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR})
