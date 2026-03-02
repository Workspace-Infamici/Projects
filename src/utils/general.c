#include "general.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

void read_string(const char *prompt, char *buf, size_t size) {
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, (int)size, stdin)) {
            clearerr(stdin);
            continue;
        }
        trim_newline(buf);
        if (buf[0] == '\0') {
            printf("Valore non valido. Riprova.\n");
            continue;
        }
        return;
    }
}

int read_int(const char *prompt, int *out) {
    char line[64];
    char *end = NULL;
    long value;

    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            clearerr(stdin);
            continue;
        }
        trim_newline(line);
        errno = 0;
        value = strtol(line, &end, 10);
        if (errno != 0 || end == line || *end != '\0') {
            printf("Numero non valido. Riprova.\n");
            continue;
        }
        *out = (int)value;
        return 1;
    }
}

int read_float(const char *prompt, float *out) {
    char line[64];
    char *end = NULL;
    float value;

    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            clearerr(stdin);
            continue;
        }
        trim_newline(line);
        errno = 0;
        value = strtof(line, &end);
        if (errno != 0 || end == line || *end != '\0') {
            printf("Numero non valido. Riprova.\n");
            continue;
        }
        *out = value;
        return 1;
    }
}

void print_generic(const void *data, PrintFn printer) {
    if (!data || !printer) {
        return;
    }
    printer(data);
}

void print_int(const void *data) {
    const int *value = (const int *)data;
    printf("%d\n", *value);
}

void print_float(const void *data) {
    const float *value = (const float *)data;
    printf("%.2f\n", *value);
}

void print_cstring(const void *data) {
    const char *value = (const char *)data;
    printf("%s\n", value ? value : "");
}
