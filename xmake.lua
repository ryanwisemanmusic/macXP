set_project("macXPKernel")
set_version("0.1.0")
set_languages("c17")

add_rules("mode.debug", "mode.release")

target("kernel_test")
    set_kind("binary")
    add_files("app/*.c")
    add_includedirs(".", "dos")
    add_cflags("-Wall", "-Wextra", "-Wpedantic", {tools = {"clang", "gcc"}})
