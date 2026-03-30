cmake_minimum_required(VERSION 3.20)
project(macXPKernel LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

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
)

target_compile_options(kernel_test
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
