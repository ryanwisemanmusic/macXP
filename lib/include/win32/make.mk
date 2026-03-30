# macOS/Linux make equivalent of make.bat for generating windows.h

OUT := windows.h

HEADER_PARTS := \
	windows_base.h \
	atomic.h \
	dbghelp.h \
	dds.h \
	file.h \
	gdi.h \
	io.h \
	misc.h \
	process.h \
	sysinfo.h \
	threads.h \
	window.h \
	intrin.h \
	fiber.h

.PHONY: all clean regen

all: $(OUT)

regen: clean all

$(OUT): $(HEADER_PARTS)
	@rm -f "$(OUT)"
	@printf '%s\n' '#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))' > "$(OUT)"
	@printf '%s\n' '#pragma once' >> "$(OUT)"
	@printf '%s\n' '#ifndef _INC_WINDOWS' >> "$(OUT)"
	@printf '%s\n' '#define _INC_WINDOWS' >> "$(OUT)"
	@printf '%s\n' '#ifndef WINDOWS_H' >> "$(OUT)"
	@printf '%s\n' '#define WINDOWS_H' >> "$(OUT)"
	@printf '\n' >> "$(OUT)"
	@for f in $(HEADER_PARTS); do \
		printf '\n' >> "$(OUT)"; \
		cat "$$f" >> "$(OUT)"; \
	done
	@printf '\n' >> "$(OUT)"
	@printf '%s\n' '#endif' >> "$(OUT)"
	@printf '%s\n' '#endif' >> "$(OUT)"
	@printf '%s\n' '#define _WINDOWS_' >> "$(OUT)"
	@printf '%s\n' '#endif' >> "$(OUT)"

clean:
	@rm -f "$(OUT)"
