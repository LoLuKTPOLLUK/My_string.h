typedef unsigned s21_size_t;

#include <stdio.h>
#include <string.h>

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strstr(const char *haystack, const char *needle) {
    int flag = 0;
    const char *ph, *pn;
    for (int i = 0; *haystack; haystack++) {
        if (needle[0] == '\0') {
            flag = 1;
            break;
        }
        if (*haystack == *needle) {
            ph = haystack;
            pn = needle;
            while (*ph && *pn && *pn == *ph) {
                pn++;
                ph++;
                i++;
            }
            if (*ph && *pn && *ph != *pn) {
            i = 0;
            } else if (i) {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0) {
        haystack = NULL;
    }
    return (char*)haystack;
}
