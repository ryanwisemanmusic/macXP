#include <stdio.h>

#include "window.h"

HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName);

static LRESULT WINAPI entrypoint_wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

static int ui_window_try_create(void) {
	const char *class_name = "macxp.win32.api.smoke";
	HINSTANCE instance = NULL;
	WNDCLASSEXA wc = {0};
	HWND hwnd;

	instance = GetModuleHandleA(NULL);
	if (instance == NULL) {
		fprintf(stderr, "[ui/window] GetModuleHandleA failed in smoke test.\n");
		return -1;
	}

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = entrypoint_wndproc;
	wc.hInstance = instance;
	wc.lpszClassName = class_name;

	if (RegisterClassExA(&wc) == 0) {
		fprintf(stderr, "[ui/window] RegisterClassExA failed in smoke test.\n");
		return -1;
	}

	hwnd = CreateWindowExA(
		0,
		class_name,
		"macXP Win32 API Smoke Test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		instance,
		NULL);

	if (hwnd == NULL) {
		fprintf(stderr, "[ui/window] CreateWindowExA failed in smoke test.\n");
		(void)UnregisterClassA(class_name, instance);
		return -1;
	}

	(void)DestroyWindow(hwnd);
	(void)UnregisterClassA(class_name, instance);
	fprintf(stderr, "[ui/window] Window creation smoke test completed.\n");
	return 0;
}

__attribute__((constructor)) static void ui_window_entrypoint_bootstrap(void) {
	(void)ui_window_try_create();
}

