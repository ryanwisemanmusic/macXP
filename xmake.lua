set_project("macXPKernel")
set_version("0.1.0")
set_languages("c17")

add_rules("mode.debug", "mode.release")

local sdl3_root = "third_party/SDL3"
if not os.isdir(sdl3_root) then
    raise("SDL3 source folder not found: " .. sdl3_root)
end

local sdl_image_root = "third_party/SDL_image"
if not os.isdir(sdl_image_root) then
    raise("SDL_image source folder not found: " .. sdl_image_root)
end

local sdl_mixer_root = "third_party/SDL_mixer"
if not os.isdir(sdl_mixer_root) then
    raise("SDL_mixer source folder not found: " .. sdl_mixer_root)
end

local libusb_root = "third_party/libusb"
if not os.isdir(libusb_root) then
    raise("libusb source folder not found: " .. libusb_root)
end

local ffmpeg_root = "third_party/FFmpeg"
if not os.isdir(ffmpeg_root) then
    raise("FFmpeg source folder not found: " .. ffmpeg_root)
end

local required_lib_files = {
    "lib/Makefile.in",
    "lib/ddk/Makefile.in",
    "lib/directx/Makefile.in",
    "lib/include/ddk",
    "lib/include/directx",
    "lib/include/gdiplus",
    "lib/include/GL",
    "lib/include/win32",
    "lib/res.rc",
    "lib/vfw32.mri"
}
local required_libce_files = {
    "libce/Makefile.in",
    "libce/directx/Makefile.in",
    "libce/res.rc"
}
for _, file in ipairs(required_lib_files) do
    if not os.isfile(file) then
        raise("Required lib file not found: " .. file)
    end
end
for _, file in ipairs(required_libce_files) do
    if not os.isfile(file) then
        raise("Required libce file not found: " .. file)
    end
end
if not os.isfile("lib/include/win32/make.mk") and not os.isfile("lib/include/win32/Makefile") then
    raise("Required win32 include make script not found: expected lib/include/win32/make.mk or lib/include/win32/Makefile")
end

local sdl3_header = path.join(sdl3_root, "include", "SDL3", "SDL.h")
if not os.isfile(sdl3_header) then
    raise("SDL3 header not found: " .. sdl3_header)
end

local sdl_image_header = path.join(sdl_image_root, "include", "SDL3_image", "SDL_image.h")
if not os.isfile(sdl_image_header) then
    raise("SDL_image header not found: " .. sdl_image_header)
end

local sdl_mixer_header = path.join(sdl_mixer_root, "include", "SDL3_mixer", "SDL_mixer.h")
if not os.isfile(sdl_mixer_header) then
    raise("SDL_mixer header not found: " .. sdl_mixer_header)
end

local libusb_header = path.join(libusb_root, "libusb", "libusb.h")
if not os.isfile(libusb_header) then
    raise("libusb header not found: " .. libusb_header)
end

local ffmpeg_header = path.join(ffmpeg_root, "libavcodec", "avcodec.h")
if not os.isfile(ffmpeg_header) then
    raise("FFmpeg header not found: " .. ffmpeg_header)
end

local sdl3_build_dir = "build/sdl3"

target("kernel_test")
    set_kind("binary")
    add_files("app/*.c")
    add_files("ui/window/*.c")
    add_files("lib/include/win32/win32functions.c")
    add_includedirs(".", "dos", "lib/include", "lib/include/ddk", "lib/include/directx", "lib/include/gdiplus", "lib/include/GL", "lib/include/win32", "libce/include")
    add_includedirs(path.join(sdl3_root, "include"))
    add_includedirs(path.join(sdl_image_root, "include"))
    add_includedirs(path.join(sdl_mixer_root, "include"))
    add_linkdirs(sdl3_build_dir)
    add_rpathdirs("@loader_path/../sdl3")
    add_links("SDL3")
    add_cflags("-Wall", "-Wextra", "-Wpedantic", {tools = {"clang", "gcc"}})
    before_build(function ()
        os.execv("sh", {"tools/check_repo_compile.sh", "lib"})
        os.execv("sh", {"tools/check_repo_compile.sh", "libce"})
    end)

target("check_tools")
    set_kind("phony")
    on_run(function ()
        os.execv("sh", {"tools/check_repo_compile.sh", "tools"})
    end)

target("check_lib")
    set_kind("phony")
    on_run(function ()
        os.execv("sh", {"tools/check_repo_compile.sh", "lib"})
    end)

target("check_libce")
    set_kind("phony")
    on_run(function ()
        os.execv("sh", {"tools/check_repo_compile.sh", "libce"})
    end)

target("check_repo_compile")
    set_kind("phony")
    on_run(function ()
        os.execv("sh", {"tools/check_repo_compile.sh", "all"})
    end)
