include mk/common.mk

# Each folder owns its own module file and contributes sources/flags.
include app/module.mk
include dos/module.mk
include ui/module.mk

.PHONY: all run clean print-config deps libusb ffmpeg sdl3

SDL3_CMAKE_GENERATOR ?= Unix Makefiles
SDL3_BUILD_DIR ?= $(BUILD_DIR)/sdl3
# Keep third-party install prefix out of workspace paths with spaces.
DEPS_PREFIX ?= /tmp/macxp-deps
DEPS_PKGCONFIG ?= $(DEPS_PREFIX)/lib/pkgconfig:$(DEPS_PREFIX)/lib64/pkgconfig

deps: libusb ffmpeg

libusb:
	@if [ ! -f "$(LIBUSB_ROOT)/configure" ]; then cd "$(LIBUSB_ROOT)" && ./autogen.sh; fi
	@cd "$(LIBUSB_ROOT)" && ./configure --prefix="$(DEPS_PREFIX)" --disable-static --enable-shared
	@$(MAKE) -C "$(LIBUSB_ROOT)"
	@$(MAKE) -C "$(LIBUSB_ROOT)" install

ffmpeg:
	@cd "$(FFMPEG_ROOT)" && ./configure --prefix="$(DEPS_PREFIX)" --enable-shared --disable-static --disable-programs --disable-doc --disable-debug
	@$(MAKE) -C "$(FFMPEG_ROOT)"
	@$(MAKE) -C "$(FFMPEG_ROOT)" install

sdl3:
	@PKG_CONFIG_PATH="$(DEPS_PKGCONFIG):$$PKG_CONFIG_PATH" cmake -S $(SDL3_ROOT) -B $(SDL3_BUILD_DIR) -G "$(SDL3_CMAKE_GENERATOR)" -DCMAKE_BUILD_TYPE=Release -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TEST=OFF
	@cmake --build $(SDL3_BUILD_DIR) --config Release

$(TARGET): $(OBJ_FILES)
	$(call ensure-dir,$@)
	$(LINKER) $(OBJ_FILES) $(LDFLAGS) $(LDLIBS) -o $@

all: deps sdl3 $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r $(BUILD_DIR)

print-config:
	@echo "TARGET=$(TARGET)"
	@echo "SRC_FILES=$(SRC_FILES)"
	@echo "OBJ_FILES=$(OBJ_FILES)"
	@echo "SDL3_ROOT=$(SDL3_ROOT)"
	@echo "SDL3_HEADER=$(SDL3_HEADER)"
	@echo "SDL_IMAGE_HEADER=$(SDL_IMAGE_HEADER)"
	@echo "SDL_MIXER_HEADER=$(SDL_MIXER_HEADER)"
	@echo "LIBUSB_HEADER=$(LIBUSB_HEADER)"
	@echo "FFMPEG_HEADER=$(FFMPEG_HEADER)"
	@echo "DEPS_PREFIX=$(DEPS_PREFIX)"
	@echo "DEPS_PKGCONFIG=$(DEPS_PKGCONFIG)"
	@echo "SDL3_LIB_DIR=$(SDL3_LIB_DIR)"
