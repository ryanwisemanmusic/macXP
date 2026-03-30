#include "window.h"
#include "win32functions.h"

#include <SDL3/SDL.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define WIN32FUNC_MAX_CLASSES 64
#define WIN32FUNC_MAX_WINDOWS 128

typedef struct {
    int in_use;
    HINSTANCE instance;
    WNDPROC proc;
    char class_name[256];
} win32_class_entry;

typedef struct {
    int in_use;
    const win32_class_entry *class_ref;
    SDL_Window *sdl_window;
    char title[256];
} win32_window_entry;

static int g_module_anchor;
static win32_class_entry g_classes[WIN32FUNC_MAX_CLASSES];
static win32_window_entry g_windows[WIN32FUNC_MAX_WINDOWS];

static LRESULT CALLBACK win32func_gate_wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

static int win32func_copy_text(char *dst, size_t dst_size, const char *src) {
    size_t n;

    if (dst == NULL || dst_size == 0 || src == NULL) {
        return 0;
    }

    n = strlen(src);
    if (n + 1 > dst_size) {
        return 0;
    }

    memcpy(dst, src, n + 1);
    return 1;
}

static win32_class_entry *win32func_find_class(const char *name, HINSTANCE instance) {
    size_t i;

    for (i = 0; i < WIN32FUNC_MAX_CLASSES; ++i) {
        if (!g_classes[i].in_use) {
            continue;
        }
        if (g_classes[i].instance != instance) {
            continue;
        }
        if (strcmp(g_classes[i].class_name, name) == 0) {
            return &g_classes[i];
        }
    }

    return NULL;
}

static win32_class_entry *win32func_alloc_class(void) {
    size_t i;

    for (i = 0; i < WIN32FUNC_MAX_CLASSES; ++i) {
        if (!g_classes[i].in_use) {
            return &g_classes[i];
        }
    }

    return NULL;
}

static win32_window_entry *win32func_alloc_window(void) {
    size_t i;

    for (i = 0; i < WIN32FUNC_MAX_WINDOWS; ++i) {
        if (!g_windows[i].in_use) {
            return &g_windows[i];
        }
    }

    return NULL;
}

HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName) {
    if (lpModuleName != NULL && lpModuleName[0] != '\0') {
        return NULL;
    }

    return (HMODULE)(uintptr_t)&g_module_anchor;
}

ATOM WINAPI RegisterClassExA(const WNDCLASSEXA *wnd_class) {
    win32_class_entry *slot;

    if (wnd_class == NULL || wnd_class->lpszClassName == NULL || wnd_class->lpfnWndProc == NULL) {
        return 0;
    }

    if (win32func_find_class(wnd_class->lpszClassName, wnd_class->hInstance) != NULL) {
        return 0;
    }

    slot = win32func_alloc_class();
    if (slot == NULL) {
        return 0;
    }

    if (!win32func_copy_text(slot->class_name, sizeof(slot->class_name), wnd_class->lpszClassName)) {
        return 0;
    }

    slot->in_use = 1;
    slot->instance = wnd_class->hInstance;
    slot->proc = wnd_class->lpfnWndProc;

    return (ATOM)((slot - g_classes) + 1);
}

BOOL WINAPI UnregisterClassA(LPCSTR lpClassName, HINSTANCE hInstance) {
    win32_class_entry *entry;

    if (lpClassName == NULL) {
        return FALSE;
    }

    entry = win32func_find_class(lpClassName, hInstance);
    if (entry == NULL) {
        return FALSE;
    }

    entry->in_use = 0;
    entry->instance = NULL;
    entry->proc = NULL;
    entry->class_name[0] = '\0';

    return TRUE;
}

HWND WINAPI CreateWindowExA(
    DWORD dwExStyle,
    LPCSTR lpClassName,
    LPCSTR lpWindowName,
    DWORD dwStyle,
    int x,
    int y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam) {
    win32_class_entry *class_entry;
    win32_window_entry *window_entry;
    const char *window_title = "macXP Win32 Window";
    int width = nWidth;
    int height = nHeight;
    SDL_WindowFlags sdl_flags = 0;

    (void)dwExStyle;
    (void)dwStyle;
    (void)x;
    (void)y;
    (void)nWidth;
    (void)nHeight;
    (void)hWndParent;
    (void)hMenu;
    (void)lpParam;

    if (lpClassName == NULL) {
        return NULL;
    }

    class_entry = win32func_find_class(lpClassName, hInstance);
    if (class_entry == NULL) {
        return NULL;
    }

    window_entry = win32func_alloc_window();
    if (window_entry == NULL) {
        return NULL;
    }

    if ((SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO) == 0) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            return NULL;
        }
    }

    if (lpWindowName != NULL && lpWindowName[0] != '\0') {
        window_title = lpWindowName;
    }

    if (width <= 0 || width == CW_USEDEFAULT) {
        width = 640;
    }

    if (height <= 0 || height == CW_USEDEFAULT) {
        height = 480;
    }

    if ((dwStyle & WS_VISIBLE) == 0) {
        sdl_flags |= SDL_WINDOW_HIDDEN;
    }

    window_entry->sdl_window = SDL_CreateWindow(window_title, width, height, sdl_flags);
    if (window_entry->sdl_window == NULL) {
        return NULL;
    }

    window_entry->in_use = 1;
    window_entry->class_ref = class_entry;
    if (lpWindowName != NULL) {
        if (!win32func_copy_text(window_entry->title, sizeof(window_entry->title), lpWindowName)) {
            SDL_DestroyWindow(window_entry->sdl_window);
            window_entry->in_use = 0;
            window_entry->class_ref = NULL;
            window_entry->sdl_window = NULL;
            return NULL;
        }
    } else {
        window_entry->title[0] = '\0';
    }

    return (HWND)(uintptr_t)window_entry;
}

LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    (void)hWnd;
    (void)uMsg;
    (void)wParam;
    (void)lParam;
    return 0;
}

BOOL WINAPI DestroyWindow(HWND hWnd) {
    win32_window_entry *window_entry;
    size_t i;
    int active_windows = 0;

    if (hWnd == NULL) {
        return FALSE;
    }

    window_entry = (win32_window_entry *)(uintptr_t)hWnd;
    if (window_entry < g_windows || window_entry >= (g_windows + WIN32FUNC_MAX_WINDOWS)) {
        return FALSE;
    }

    if (!window_entry->in_use) {
        return FALSE;
    }

    if (window_entry->sdl_window == NULL) {
        return FALSE;
    }

    SDL_DestroyWindow(window_entry->sdl_window);

    window_entry->in_use = 0;
    window_entry->class_ref = NULL;
    window_entry->sdl_window = NULL;
    window_entry->title[0] = '\0';

    for (i = 0; i < WIN32FUNC_MAX_WINDOWS; ++i) {
        if (g_windows[i].in_use) {
            active_windows = 1;
            break;
        }
    }

    if (!active_windows && (SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO) != 0) {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    return TRUE;
}

int win32functions_gate_windowing(void) {
    const char *class_name = "macxp.win32functions.gate";
    HINSTANCE instance = NULL;
    WNDCLASSEXA wc = {0};
    HWND hwnd = NULL;

    instance = GetModuleHandleA(NULL);
    if (instance == NULL) {
        return WIN32FUNC_GATE_MODULE_HANDLE_FAILED;
    }

    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = win32func_gate_wndproc;
    wc.hInstance = instance;
    wc.lpszClassName = class_name;

    if (RegisterClassExA(&wc) == 0) {
        return WIN32FUNC_GATE_REGISTER_CLASS_FAILED;
    }

    hwnd = CreateWindowExA(
        0,
        class_name,
        "macXP Win32 Gate",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        640,
        480,
        NULL,
        NULL,
        instance,
        NULL);

    if (hwnd == NULL) {
        (void)UnregisterClassA(class_name, instance);
        return WIN32FUNC_GATE_CREATE_WINDOW_FAILED;
    }

    if (!DestroyWindow(hwnd)) {
        (void)UnregisterClassA(class_name, instance);
        return WIN32FUNC_GATE_DESTROY_WINDOW_FAILED;
    }

    if (!UnregisterClassA(class_name, instance)) {
        return WIN32FUNC_GATE_UNREGISTER_CLASS_FAILED;
    }

    return WIN32FUNC_GATE_OK;
}

int win32functions_smoke_visible_window(unsigned int duration_ms) {
    const char *class_name = "macxp.win32functions.smoke";
    HINSTANCE instance = NULL;
    WNDCLASSEXA wc = {0};
    HWND hwnd = NULL;

    instance = GetModuleHandleA(NULL);
    if (instance == NULL) {
        return WIN32FUNC_GATE_MODULE_HANDLE_FAILED;
    }

    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = win32func_gate_wndproc;
    wc.hInstance = instance;
    wc.lpszClassName = class_name;

    if (RegisterClassExA(&wc) == 0) {
        return WIN32FUNC_GATE_REGISTER_CLASS_FAILED;
    }

    hwnd = CreateWindowExA(
        0,
        class_name,
        "macXP Win32->SDL3 Smoke",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        480,
        NULL,
        NULL,
        instance,
        NULL);

    if (hwnd == NULL) {
        (void)UnregisterClassA(class_name, instance);
        return WIN32FUNC_GATE_CREATE_WINDOW_FAILED;
    }

    SDL_PumpEvents();
    SDL_Delay(duration_ms == 0 ? 800u : duration_ms);

    if (!DestroyWindow(hwnd)) {
        (void)UnregisterClassA(class_name, instance);
        return WIN32FUNC_GATE_DESTROY_WINDOW_FAILED;
    }

    if (!UnregisterClassA(class_name, instance)) {
        return WIN32FUNC_GATE_UNREGISTER_CLASS_FAILED;
    }

    return WIN32FUNC_GATE_OK;
}

const char *win32functions_gate_error_string(int gate_code) {
    switch (gate_code) {
        case WIN32FUNC_GATE_OK:
            return "ok";
        case WIN32FUNC_GATE_MODULE_HANDLE_FAILED:
            return "GetModuleHandleA failed";
        case WIN32FUNC_GATE_REGISTER_CLASS_FAILED:
            return "RegisterClassExA failed";
        case WIN32FUNC_GATE_CREATE_WINDOW_FAILED:
            return "CreateWindowExA failed";
        case WIN32FUNC_GATE_DESTROY_WINDOW_FAILED:
            return "DestroyWindow failed";
        case WIN32FUNC_GATE_UNREGISTER_CLASS_FAILED:
            return "UnregisterClassA failed";
        default:
            return "unknown gate error";
    }
}
