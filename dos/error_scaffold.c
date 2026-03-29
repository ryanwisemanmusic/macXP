#include "error_scaffold.h"

#include "error_codes.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_banner(void) {
    puts("DOS error scaffold");
    puts("enter a numeric error code (0-15), 'help', or 'quit'");
}

static void print_help(void) {
    puts("commands:");
    puts("  0..15 - run HANDLE_ERROR for that ErrorCode value");
    puts("  help  - show this help text");
    puts("  quit  - exit scaffold");
}

void dos_error_check_code(int raw_code) {
    if (raw_code < (int)SUCCESS || raw_code > (int)CANNOT_WRITE) {
        puts("invalid error code range; expected 0-15");
        return;
    }

    HANDLE_ERROR((ErrorCode)raw_code);
}

static int parse_code(const char *line, int *out_code) {
    char *end = NULL;
    long value = 0;

    errno = 0;
    value = strtol(line, &end, 10);

    if (end == line) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    if (errno != 0) {
        return 0;
    }

    *out_code = (int)value;
    return 1;
}

int dos_error_scaffold_run(void) {
    char line[128];

    print_banner();

    for (;;) {
        int code = 0;

        fputs("error> ", stdout);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            puts("\ninput stream closed");
            return 0;
        }

        line[strcspn(line, "\r\n")] = '\0';

        if (strcmp(line, "quit") == 0 || strcmp(line, "exit") == 0) {
            puts("leaving DOS error scaffold");
            return 0;
        }

        if (strcmp(line, "help") == 0) {
            print_help();
            continue;
        }

        if (line[0] == '\0') {
            continue;
        }

        if (!parse_code(line, &code)) {
            puts("invalid input; type 'help' or enter 0-15");
            continue;
        }

        dos_error_check_code(code);
    }
}
