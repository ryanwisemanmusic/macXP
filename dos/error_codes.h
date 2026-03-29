#ifndef ERROR_CODES_H
#define ERROR_CODES_H
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum ErrorCode {
    SUCCESS,
    ACCESS_DENIED,
    INVALID_ID_FOR_FUNCTION,
    INVALID_ID_FOR_PARAMETER,
    REGISTER_TO_IO_FAILURE,
    FAILED_GET_ADDRESS_FETCH,
    FAILED_GET_FILE,
    FAILED_ALLOCATION,
    MEM_FAILED_NO_LEFT,
    INVALID_KEY,
    DELETED_KEY,
    CANNOT_LOCK,
    CANNOT_OPEN,
    CANNOT_CLOSE,
    CANNOT_READ,
    CANNOT_WRITE
} ErrorCode;

#define HANDLE_ERROR(code)                                 \
    do {                                                   \
        switch (code) {                                    \
            case SUCCESS:                                  \
                write(1, "success\n", 8);                  \
                break;                                     \
            case ACCESS_DENIED:                            \
                write(2, "access denied\n", 14);           \
                break;                                     \
            case INVALID_ID_FOR_FUNCTION:                  \
                write(2, "invalid function id\n", 20);     \
                break;                                     \
            case INVALID_ID_FOR_PARAMETER:                 \
                write(2, "invalid parameter id\n", 21);    \
                break;                                     \
            case REGISTER_TO_IO_FAILURE:                   \
                write(2, "register io failure\n", 20);     \
                break;                                     \
            case FAILED_GET_ADDRESS_FETCH:                 \
                write(2, "failed getting address\n", 24);  \
                break;                                     \
            case FAILED_GET_FILE:                          \
                write(2, "failed getting file\n", 20);     \
                break;                                     \
            case FAILED_ALLOCATION:                        \
                write(2, "allocation failure\n", 19);      \
                break;                                     \
            case MEM_FAILED_NO_LEFT:                       \
                write(2, "no memory left\n", 15);          \
                break;                                     \
            case INVALID_KEY:                              \
                write(2, "invalid key\n", 12);             \
                break;                                     \
            case DELETED_KEY:                              \
                write(2, "deleted key\n", 12);             \
                break;                                     \
            case CANNOT_LOCK:                              \
                write(2, "cannot lock\n", 12);             \
                break;                                     \
            case CANNOT_OPEN:                              \
                write(2, "cannot open\n", 12);             \
                break;                                     \
            case CANNOT_CLOSE:                             \
                write(2, "cannot close\n", 13);            \
                break;                                     \
            case CANNOT_READ:                              \
                write(2, "cannot read\n", 12);             \
                break;                                     \
            case CANNOT_WRITE:                             \
                write(2, "cannot write\n", 13);            \
                break;                                     \
        }                                                  \
    } while (0)

#endif
