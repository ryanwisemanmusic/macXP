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
set(LIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(LIBCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libce")
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

set(REQUIRED_LIB_FILES
    "${LIB_ROOT}/Makefile.in"
    "${LIB_ROOT}/ddk/Makefile.in"
    "${LIB_ROOT}/directx/Makefile.in"
    "${LIB_ROOT}/include/ddk"
    "${LIB_ROOT}/include/directx"
    "${LIB_ROOT}/include/gdiplus"
    "${LIB_ROOT}/include/GL"
    "${LIB_ROOT}/include/win32"
    "${LIB_ROOT}/res.rc"
    "${LIB_ROOT}/vfw32.mri"
)
set(REQUIRED_LIBCE_FILES
    "${LIBCE_ROOT}/Makefile.in"
    "${LIBCE_ROOT}/directx/Makefile.in"
    "${LIBCE_ROOT}/res.rc"
)
foreach(required_file IN LISTS REQUIRED_LIB_FILES REQUIRED_LIBCE_FILES)
    if(NOT EXISTS "${required_file}")
        message(FATAL_ERROR "Required library file missing: ${required_file}")
    endif()
endforeach()

if(NOT EXISTS "${LIB_ROOT}/include/win32/make.mk" AND NOT EXISTS "${LIB_ROOT}/include/win32/Makefile")
    message(FATAL_ERROR "Required win32 include make script missing: expected ${LIB_ROOT}/include/win32/make.mk or ${LIB_ROOT}/include/win32/Makefile")
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
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/ddk
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/directx
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/gdiplus
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/GL
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include/win32
    ${CMAKE_CURRENT_SOURCE_DIR}/libce/include
        ${SDL3_INCLUDE_DIR}
        ${SDL_IMAGE_ROOT}/include
        ${SDL_MIXER_ROOT}/include
)

target_link_libraries(kernel_test
    PRIVATE
        SDL3::SDL3
)

set_target_properties(kernel_test PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/third_party/sdl3"
)

target_compile_options(kernel_test
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_custom_target(check_tools
    COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/tools/check_repo_compile.sh" tools
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_target(check_lib
    COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/tools/check_repo_compile.sh" lib
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_target(check_libce
    COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/tools/check_repo_compile.sh" libce
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_target(check_repo_compile
    COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/tools/check_repo_compile.sh" all
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_target(check_w32api
    DEPENDS check_lib check_libce
)

add_dependencies(kernel_test check_w32api)
