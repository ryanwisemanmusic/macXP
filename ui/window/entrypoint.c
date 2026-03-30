#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>

static void ui_window_header_probe(void) {
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;
	IMG_Animation *image_animation = NULL;

	(void)window;
	(void)surface;
	(void)image_animation;
}

__attribute__((constructor)) static void ui_window_entrypoint_bootstrap(void) {
	ui_window_header_probe();
	fprintf(stderr, "[ui/window] SDL headers resolved (SDL3, SDL_image, SDL_mixer).\n");
}

