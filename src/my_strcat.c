#include <stdio.h>

typedef unsigned my_size_t;

char *my_strcat(char *dest, const char *src);
my_size_t my_strlen(const char *str);

char *my_strcat(char *dest, const char *src) {
    char *t;
    for (t = dest; *t; ++t);
    while (*t++ += *src++);
    return dest;
}

my_size_t my_strlen(const char *str) {
    const char* cur = str;
    for (; *cur; ++cur) {
    }
    return cur - str;
}
