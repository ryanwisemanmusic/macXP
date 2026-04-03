CC ?= cc
CXX ?= c++

BUILD_DIR ?= build
BIN_DIR ?= $(BUILD_DIR)/bin
OBJ_DIR ?= $(BUILD_DIR)/obj
DEP_DIR ?= $(BUILD_DIR)/dep

SDL3_VERSION_FILE ?= third_party/SDL3_VERSION
SDL3_VERSION ?= $(strip $(shell cat $(SDL3_VERSION_FILE) 2>/dev/null))
SDL3_ROOT ?= third_party/SDL3
SDL_IMAGE_ROOT ?= third_party/SDL_image
SDL_MIXER_ROOT ?= third_party/SDL_mixer
LIBUSB_ROOT ?= third_party/libusb
FFMPEG_ROOT ?= third_party/FFmpeg
SDL3_INCLUDE_DIR ?= $(SDL3_ROOT)/include
SDL_IMAGE_INCLUDE_DIR ?= $(SDL_IMAGE_ROOT)/include
SDL_MIXER_INCLUDE_DIR ?= $(SDL_MIXER_ROOT)/include
SDL3_LIB_DIR ?= $(BUILD_DIR)/sdl3
SDL3_HEADER ?= $(firstword $(wildcard $(SDL3_INCLUDE_DIR)/SDL3/SDL.h))
SDL_IMAGE_HEADER ?= $(firstword $(wildcard $(SDL_IMAGE_INCLUDE_DIR)/SDL3_image/SDL_image.h))
SDL_MIXER_HEADER ?= $(firstword $(wildcard $(SDL_MIXER_INCLUDE_DIR)/SDL3_mixer/SDL_mixer.h))
LIBUSB_HEADER ?= $(firstword $(wildcard $(LIBUSB_ROOT)/libusb/libusb.h))
FFMPEG_HEADER ?= $(firstword $(wildcard $(FFMPEG_ROOT)/libavcodec/avcodec.h))

# Baseline flags are intentionally conservative for portability.
CPPFLAGS += -I. -Idos -Ilib/include -Ilib/include/win32 -Ilibce/include
CFLAGS += -std=c17 -Wall -Wextra -Wpedantic -O2
CXXFLAGS += -std=c++20 -Wall -Wextra -Wpedantic -O2
LDFLAGS +=
LDLIBS +=

ifeq ($(strip $(SDL3_ROOT)),)
$(error SDL3 not found. Expected third_party/SDL3)
endif

ifeq ($(strip $(SDL3_HEADER)),)
$(error SDL3 header missing: expected $(SDL3_INCLUDE_DIR)/SDL3/SDL.h)
endif

ifeq ($(strip $(SDL_IMAGE_HEADER)),)
$(error SDL_image header missing: expected $(SDL_IMAGE_INCLUDE_DIR)/SDL3_image/SDL_image.h)
endif

ifeq ($(strip $(SDL_MIXER_HEADER)),)
$(error SDL_mixer header missing: expected $(SDL_MIXER_INCLUDE_DIR)/SDL3_mixer/SDL_mixer.h)
endif

ifeq ($(strip $(LIBUSB_HEADER)),)
$(error libusb header missing: expected $(LIBUSB_ROOT)/libusb/libusb.h)
endif

ifeq ($(strip $(FFMPEG_HEADER)),)
$(error FFmpeg header missing: expected $(FFMPEG_ROOT)/libavcodec/avcodec.h)
endif

CPPFLAGS += -I$(SDL3_INCLUDE_DIR)
CPPFLAGS += -I$(SDL_IMAGE_INCLUDE_DIR)
CPPFLAGS += -I$(SDL_MIXER_INCLUDE_DIR)
LDFLAGS += -L$(SDL3_LIB_DIR)
LDFLAGS += -Wl,-rpath,@loader_path/../sdl3
LDLIBS += -lSDL3

TARGET ?= $(BIN_DIR)/kernel_test

SRC_FILES ?=
C_SRC_FILES = $(filter %.c,$(SRC_FILES))
CXX_SRC_FILES = $(filter %.cpp,$(SRC_FILES))

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_SRC_FILES)) \
	$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CXX_SRC_FILES))
DEP_FILES = $(patsubst %.c,$(DEP_DIR)/%.d,$(C_SRC_FILES)) \
	$(patsubst %.cpp,$(DEP_DIR)/%.d,$(CXX_SRC_FILES))

LINKER = $(if $(filter %.cpp,$(SRC_FILES)),$(CXX),$(CC))

MKDIR_P ?= mkdir -p
RM ?= rm -f

define ensure-dir
	@$(MKDIR_P) $(dir $1)
endef

# Compile each translation unit into a mirrored object path.
$(OBJ_DIR)/%.o: %.c
	$(call ensure-dir,$@)
	$(call ensure-dir,$(DEP_DIR)/$*.d)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(call ensure-dir,$@)
	$(call ensure-dir,$(DEP_DIR)/$*.d)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

-include $(DEP_FILES)
