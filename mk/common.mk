CC ?= cc
CXX ?= c++

BUILD_DIR ?= build
BIN_DIR ?= $(BUILD_DIR)/bin
OBJ_DIR ?= $(BUILD_DIR)/obj
DEP_DIR ?= $(BUILD_DIR)/dep

# Baseline flags are intentionally conservative for portability.
CPPFLAGS += -I. -Idos -Ilib/include/win32
CFLAGS += -std=c17 -Wall -Wextra -Wpedantic -O2
CXXFLAGS += -std=c++20 -Wall -Wextra -Wpedantic -O2
LDFLAGS +=
LDLIBS +=

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
