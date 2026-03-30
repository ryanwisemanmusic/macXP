cmake_minimum_required(VERSION 3.20)
project(macXPKernel LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SDL3_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL3")
if(NOT EXISTS "${SDL3_ROOT}/CMakeLists.txt")
    message(FATAL_ERROR "SDL3 source not found at ${SDL3_ROOT}. Did you init submodules?")
endif()

set(SDL_IMAGE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL_image")
set(SDL_MIXER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL_mixer")
set(LIBUSB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/libusb")
set(FFMPEG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/FFmpeg")
if(NOT EXISTS "${SDL_IMAGE_ROOT}/include/SDL3_image/SDL_image.h")
    message(FATAL_ERROR "SDL_image header not found: ${SDL_IMAGE_ROOT}/include/SDL3_image/SDL_image.h")
endif()
if(NOT EXISTS "${SDL_MIXER_ROOT}/include/SDL3_mixer/SDL_mixer.h")
    message(FATAL_ERROR "SDL_mixer header not found: ${SDL_MIXER_ROOT}/include/SDL3_mixer/SDL_mixer.h")
endif()
if(NOT EXISTS "${LIBUSB_ROOT}/libusb/libusb.h")
    message(FATAL_ERROR "libusb header not found: ${LIBUSB_ROOT}/libusb/libusb.h")
endif()
if(NOT EXISTS "${FFMPEG_ROOT}/libavcodec/avcodec.h")
    message(FATAL_ERROR "FFmpeg header not found: ${FFMPEG_ROOT}/libavcodec/avcodec.h")
endif()

set(SDL3_INCLUDE_DIR "${SDL3_ROOT}/include")
set(SDL3_INCLUDE_HEADER "${SDL3_INCLUDE_DIR}/SDL3/SDL.h")
if(NOT EXISTS "${SDL3_INCLUDE_HEADER}")
    message(FATAL_ERROR "SDL3 header not found: ${SDL3_INCLUDE_HEADER}")
endif()

set(SDL_SHARED ON CACHE BOOL "Build shared SDL3" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Build static SDL3" FORCE)
set(SDL_TEST OFF CACHE BOOL "Build SDL3 tests" FORCE)

set(DEPS_PREFIX "${CMAKE_BINARY_DIR}/deps")
set(ENV{PKG_CONFIG_PATH} "${DEPS_PREFIX}/lib/pkgconfig:${DEPS_PREFIX}/lib64/pkgconfig:$ENV{PKG_CONFIG_PATH}")
add_subdirectory("${SDL3_ROOT}" "${CMAKE_BINARY_DIR}/third_party/sdl3")

add_executable(kernel_test
    app/main.c
    app/scaffold.c
    ui/window/entrypoint.c
    lib/include/win32/win32functions.c
)

target_include_directories(kernel_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/dos
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/win32
        ${SDL3_INCLUDE_DIR}
        ${SDL_IMAGE_ROOT}/include
        ${SDL_MIXER_ROOT}/include
)

target_link_libraries(kernel_test
    PRIVATE
        SDL3::SDL3
)

target_compile_options(kernel_test
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
