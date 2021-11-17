#include <stdio.h>

typedef unsigned s21_size_t;

char *s21_strncat(char *dest, const char *src, s21_size_t n);

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    int i = 0, j = 0;
    while (dest[i] != '\0') {
        i++;
    }
    while (j != n) {
        dest[i] += src[j];
        i++;
        j++;
    }
    return dest;
}
