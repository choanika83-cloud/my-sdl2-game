cmake_minimum_required(VERSION 3.23)

# 1. Define the project
project(
    MyGame
    VERSION 1.0
    DESCRIPTION "My SDL2 Game"
    LANGUAGES CXX
)

# 2. Force Vendored Libraries for SDL and SDL_image
set(SDL2_VENDORED ON CACHE BOOL "" FORCE)
set(SDL_IMAGE_VENDORED ON CACHE BOOL "" FORCE)

# 3. Project Settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")

# 4. Output Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# 5. Define Executable
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(MyGame ${SOURCES})

# 6. OS Specific RPATH
if(APPLE) 
    set_target_properties(MyGame PROPERTIES
        INSTALL_RPATH "@executable_path;@loader_path"
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_RPATH TRUE)
elseif(UNIX)
    set_target_properties(MyGame PROPERTIES
        INSTALL_RPATH "$ORIGIN"
        BUILD_WITH_INSTALL_RPATH TRUE)
endif()

# 7. Add Subdirectories (Excluding TTF)
add_subdirectory(${VENDOR_DIR}/SDL) 
add_subdirectory(${VENDOR_DIR}/SDL_image) 

# 8. Link Libraries (Excluding TTF)
target_link_libraries(MyGame
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
)