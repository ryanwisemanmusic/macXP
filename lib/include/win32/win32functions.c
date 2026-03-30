#include "window.h"

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
    char title[256];
} win32_window_entry;

static int g_module_anchor;
static win32_class_entry g_classes[WIN32FUNC_MAX_CLASSES];
static win32_window_entry g_windows[WIN32FUNC_MAX_WINDOWS];

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

    window_entry->in_use = 1;
    window_entry->class_ref = class_entry;
    if (lpWindowName != NULL) {
        if (!win32func_copy_text(window_entry->title, sizeof(window_entry->title), lpWindowName)) {
            window_entry->in_use = 0;
            window_entry->class_ref = NULL;
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

    window_entry->in_use = 0;
    window_entry->class_ref = NULL;
    window_entry->title[0] = '\0';

    return TRUE;
}
