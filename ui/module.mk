UI_DIR := ui

UI_SRC := \
	$(UI_DIR)/window/entrypoint.c

WIN32_RUNTIME_SRC := \
	lib/include/win32/win32functions.c

SRC_FILES += $(UI_SRC) $(WIN32_RUNTIME_SRC)
