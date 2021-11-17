#include <stdio.h>

typedef unsigned s21_size_t;

char *s21_strcat(char *dest, const char *src);
s21_size_t s21_strlen(const char *str);

char *s21_strcat(char *dest, const char *src) {
    char *t;
    for (t = dest; *t; ++t);
    while (*t++ += *src++);
    return dest;
}

s21_size_t s21_strlen(const char *str) {
    const char* cur = str;
    for (; *cur; ++cur) {
    }
    return cur - str;
}
