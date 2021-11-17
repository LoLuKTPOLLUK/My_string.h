#include <stdio.h>
#include <string.h>

typedef unsigned s21_size_t;

void *s21_memset(void *str, int c, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *string = (unsigned char*)str;
    unsigned char *res = NULL;
    for (int i = 0; i != n; i++) {
        string[i] = c;
    }
    res = string;
    return res;
}
