#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "win32functions.h"

static void ui_window_header_probe(void) {
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;
	IMG_Animation *image_animation = NULL;

	(void)window;
	(void)surface;
	(void)image_animation;
}

__attribute__((constructor)) static void ui_window_entrypoint_bootstrap(void) {
	int gate_code = win32functions_gate_windowing();

	if (gate_code != WIN32FUNC_GATE_OK) {
		fprintf(stderr,
			"[ui/window] Win32 gate failed: %s. SDL path blocked.\n",
			win32functions_gate_error_string(gate_code));
		return;
	}

	gate_code = win32functions_smoke_visible_window(900);
	if (gate_code != WIN32FUNC_GATE_OK) {
		fprintf(stderr,
			"[ui/window] Win32 visible smoke failed: %s. SDL path blocked.\n",
			win32functions_gate_error_string(gate_code));
		return;
	}

	ui_window_header_probe();
	fprintf(stderr, "[ui/window] Win32 gate passed. Visible create/destroy smoke passed. SDL headers resolved (SDL3, SDL_image, SDL_mixer).\n");
}

