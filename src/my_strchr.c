#include <stdio.h>

typedef unsigned my_size_t;

char *my_strchr(const char *str, int c);

char *my_strchr(const char *str, int c) {
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

