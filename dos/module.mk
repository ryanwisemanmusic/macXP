DOS_DIR := dos

DOS_HEADERS := \
	$(DOS_DIR)/dos_16_types.h \
	$(DOS_DIR)/error_codes.h \
	$(DOS_DIR)/error_scaffold.h

DOS_SRC := \
	$(DOS_DIR)/error_scaffold.c

SRC_FILES += $(DOS_SRC)
