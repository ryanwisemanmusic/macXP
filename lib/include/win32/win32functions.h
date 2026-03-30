#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
#ifndef WINDOWS_WIN32FUNCTIONS_H
#define WINDOWS_WIN32FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
    WIN32FUNC_GATE_OK = 0,
    WIN32FUNC_GATE_MODULE_HANDLE_FAILED = 1,
    WIN32FUNC_GATE_REGISTER_CLASS_FAILED = 2,
    WIN32FUNC_GATE_CREATE_WINDOW_FAILED = 3,
    WIN32FUNC_GATE_DESTROY_WINDOW_FAILED = 4,
    WIN32FUNC_GATE_UNREGISTER_CLASS_FAILED = 5
};

int win32functions_gate_windowing(void);
const char *win32functions_gate_error_string(int gate_code);
int win32functions_smoke_visible_window(unsigned int duration_ms);

#ifdef __cplusplus
}
#endif

#endif /* WINDOWS_WIN32FUNCTIONS_H */
#endif
