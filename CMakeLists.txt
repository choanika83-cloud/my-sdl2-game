cmake_minimum_required(VERSION 3.23)

# 1. Define the project
project(
    snakeGame
    VERSION 1.0
    DESCRIPTION "My SDL2 Game"
    LANGUAGES C CXX
)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_LIBRARIES 1)
set(CMAKE_C_USE_RESPONSE_FILE_FOR_LIBRARIES 1)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vendor/SDL;${CMAKE_SOURCE_DIR}/vendor/SDL_image;${CMAKE_SOURCE_DIR}/vendor/SDL_ttf")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-keep-memory -Wl,--reduce-memory-overheads")

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)


# 2. Force Vendored Libraries
set(SDL2_TTF_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2_TTF_FREETYPE ON CACHE BOOL "" FORCE)
set(SDL2_TTF_HARFBUZZ OFF CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)

# 3. Project Settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")

# 4. Output Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_compile_options(-Os)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -s")

# 7. Add Subdirectories 
set(SDL2_IMAGE_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2_IMAGE_BACKEND_STB ON CACHE BOOL "" FORCE) 
set(SDL2_IMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDL2_IMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDL2_IMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDL2_IMAGE_AVIF OFF CACHE BOOL "" FORCE)


set(SDL2_TTF_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2_TTF_HARFBUZZ OFF CACHE BOOL "" FORCE)

set(FREETYPE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL_ttf/external/freetype")


set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
set(CMAKE_LINK_SEARCH_START_STATIC ON)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/SDL_ttf)

# 5. Define Executable
add_executable(snakeGame "src/snake.cpp")
target_include_directories(snakeGame PRIVATE 
    "${VENDOR_DIR}/SDL/include"
    "${VENDOR_DIR}/SDL_image/include"
    "${VENDOR_DIR}/SDL_ttf"
    "${VENDOR_DIR}/SDL_ttf/include"
)

# 6. OS Specific RPATH
if(APPLE) 
    set_target_properties(snakeGame PROPERTIES
        INSTALL_RPATH "@executable_path;@loader_path"
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_RPATH TRUE)
elseif(UNIX)
    set_target_properties(snakeGame PROPERTIES
        INSTALL_RPATH "$ORIGIN"
        BUILD_WITH_INSTALL_RPATH TRUE)
endif()



# 8. Link Libraries (Excluding TTF)
    target_link_libraries(snakeGame
   SDL2_ttf
    SDL2_image
    SDL2main
    SDL2-static
    freetype
    z
    bz2
    user32 gdi32 winmm imm32 ole32 oleaut32 shell32 setupapi version uuid
)