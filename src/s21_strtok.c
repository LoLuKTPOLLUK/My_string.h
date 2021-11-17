typedef unsigned s21_size_t;

#include <stdio.h>
#include <string.h>

char *s21_strtok(char *str, const char *delim);

char *s21_strtok(char *str, const char *delim) {
    int flag = 0, len = 0;
    static char *s = NULL;
    char *tok = {0};
    const char *p = {0};
    if (!str) {
        if (!s) return NULL;
    } else s = str;
    if (!*s) return NULL;
    len = strlen(delim);
    while (*delim) {
        if (*str != *delim) {
            flag = 1;
            break;
        }
        if (*delim == ' ') {
            len--;
        }
        str++;
        delim++;
    }
    if (flag == 0) tok = s + len;
    else if (str[0] == delim[0] && delim[1] == '\0') tok = ++s;
    else tok = s++;
    for (; *s; s++) {
        for (p = delim; *p && *s != *p; p++) {}
        if (*p) break;
    }
        if (*s) {
            *s = '\0';
            s++;
        }
    return tok;
}
