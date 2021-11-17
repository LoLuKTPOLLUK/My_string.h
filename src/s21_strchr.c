#include <stdio.h>

typedef unsigned s21_size_t;

char *s21_strchr(const char *str, int c);

char *s21_strchr(const char *str, int c) {
    char *result = NULL;
    while (*str != '\0') {
        if (*str == c) {
            result = (char*)str;
            break;
        }
        str++;
    }
    return result;
}

