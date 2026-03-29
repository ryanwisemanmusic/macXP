include mk/common.mk

# Each folder owns its own module file and contributes sources/flags.
include app/module.mk
include dos/module.mk

.PHONY: all run clean print-config

$(TARGET): $(OBJ_FILES)
	$(call ensure-dir,$@)
	$(LINKER) $(OBJ_FILES) $(LDFLAGS) $(LDLIBS) -o $@

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r $(BUILD_DIR)

print-config:
	@echo "TARGET=$(TARGET)"
	@echo "SRC_FILES=$(SRC_FILES)"
	@echo "OBJ_FILES=$(OBJ_FILES)"
