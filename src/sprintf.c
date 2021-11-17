#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "my_sprintf.h"

typedef unsigned my_size_t;

struct f {
    int pluses;
    int minuses;
    int spaces;
    int grids;
    int zeros;
    int dots;
    int nums;
    int skip;
} f;

int my_sprintf(char *str, const char *format, ...);
char *my_strcat(char *dest, const char *src);
char *my_itoa(int num);
void my_dtos(char *str, double num, double precision);
void my_clear(char* str);
char *my_parser(const char *format, char *token_str, int *counter);
int my_sscanf(const char *str, const char *format, ...);
int start_processing(char *str, char*format, va_list argptr);
void my_reverse_str(char *dest, char *str);
int check_int(char c);
int check_string(const char *str, int counter);
void check_flags(char *str, char *token_str, va_list argptr);
void processing_c(char *str, char *token_str, va_list argptr);
void processing_s(char *str, char *token_str, va_list argptr);
void while_d(char *str, char *token_str, char *num, int len, int i);
void while_c(char *str, char *token_str, char *num, int len, int i);
void processing_d(char *str, char *token_str, va_list argptr);
void main_process(char *str, char *token_str, va_list argptr, char spec);

int main() {
    char str[100];
    printf("%s", str);
}

char *my_parser(const char *format, char *token_str, int *counter) {
    int i = 0, j = 0, s = 0, flag = 0;
    while (format) {
        if (check_specs(*format)) {
            break;
        }
        *counter+=1;
        token_str[i] = *format;
        format++;
        i++;
    }
    token_str[i] = *format;
    token_str[i + 1] = '\0';
    return token_str;
}

void while_c(char *str, char *token_str, char *num, int len, int i) {
    char token[10000] = {0};
    int token_len, j;
    while (token_str[i] != 'c') {
        num[j] = token_str[i];
        i++;
        j++;
    }
    len = atoi(num);
    if (len < 0) {
        len *= -1;
    }
    while (len - 1 != 0) {
        my_strcat(str, " ");
        len--;
    }
}

void while_d(char *str, char *token_str, char *num, int len, int i) {
    char token[10000] = {0};
    int token_len, j;
    while (token_str[i] != 'd') {
        token[j] = token_str[i];
        i++;
        j++;
    }
    token[j++] = '\0';
    token_len = atoi(token);
    if (token_len < 0) {
        token_len *= -1;
    }
    if (f.pluses == 1 && num[0] != '-') {
        token_len--;
        my_strcat(str, "+");
    }
    my_strcat(str, num);
    if (token_len != len) {
        while (token_len > len) {
            my_strcat(str, " ");
            len++;
        }
    }
}

void processing_d(char *str, char *token_str, va_list argptr) {
    char *num = {0}, *string = {0}, token[10000] = {0};
    int i = 0, j = 0, x = 0, len = 0, token_len = 0;
    int tmp;
    tmp = va_arg(argptr, int);
    num = my_itoa(tmp);
    len = my_strlen(num);
    if (f.minuses == 0 && f.pluses == 0 && f.spaces == 0 && f.zeros == 0) {
        printf("A\n");
        if (check_int(token_str[i])) {
            while_d(str, token_str, num, len, i);
        }
        //my_strcat(str, num);
    } else if (f.minuses == 1) {// && f.spaces == 0) {
        printf("B\n");
        i++;
        while_d(str, token_str, num, len, i);
        //my_strcat(str, num);
    } else if (f.minuses == 1 && f.spaces == 1) {
        printf("C\n");
        if (token_str[i] == ' ' || token_str[i + 1] == ' ') {
            my_strcat(str, " ");
            len++;
            i+=2;
        }
        //my_strcat(str, num);
        while_d(str, token_str, num, len, i);
    } else if (f.pluses == 1 && f.minuses == 0 && f.spaces == 0) {
        printf("D\n");
        i++;
        if (check_int(token_str[i])) {
            while_d(str, token_str, num, len, i);
        }
        //my_strcat(str, num);
    } else {
        printf("This flag results in undefined behaviour with 'd' conversion specifier\n");
        //my_strcat(str, num);
        f.skip = 1;
    }
}

void check_flags(char *str, char *token_str, va_list argptr) {
    int i = 0;
    f.pluses = f.minuses = f.spaces = f.grids = f.zeros = 0;
    while (token_str[i] != '\0') {
        if (token_str[i - 1] == '+') {
            f.pluses = 1;
        }
        if (token_str[i - 1] == '-') {
            f.minuses = 1;
        }
        if (token_str[i - 1] == ' ') {
            f.spaces = 1;
        }
        if (token_str[i - 1] == '#') {
            f.grids = 1;
        }
        if (token_str[i - 1] == '0') {
            f.zeros = 1;
        }
        if (check_int(token_str[i - 1])) {
            f.nums = 1;
        }
        i++;
    }
}

void processing_c(char *str, char *token_str, va_list argptr) {
    char num[1000000] = {0}, *string = {0};
    int i = 0, j = 0, x = 0, len = 0;
    char tmp = {0};
    tmp = va_arg(argptr, int);
    if (f.zeros == 1 || f.pluses == 1 || f.grids == 1 || f.dots == 1) {
        printf("This flag results in undefined behaviour with 'c' conversion specifier\n");
    }
    if (f.minuses == 1) {
        i++;
        my_strcat(str, &tmp);
        while_c(str, token_str, num, len, i);
    } else if (f.nums == 1) {
        while_c(str, token_str, num, len, i);
        my_strcat(str, &tmp);
    }
}

void processing_s(char *str, char *token_str, va_list argptr) {

}

void main_process(char *str, char *token_str, va_list argptr, char spec) {
    switch (spec) {
        case 'c':
            processing_c(str, token_str, argptr);
            break;
        case 'd':
            processing_d(str, token_str, argptr);
            break;
            case 's':
            processing_s(str, token_str, argptr);
            break;
        default:;
    }
}

int start_processing(char *str, char *format, va_list argptr) {
    int i = 0, j = 0, tmp = 0;
    char *num = {0}, spec = {0};
    my_size_t len = my_strlen(format);
    while (format[i] != '\0') {
        if (check_specs(format[i])) {
            spec = format[i];
        }
        i++;
    }
    check_flags(str, format, argptr);
    main_process(str, format, argptr, spec);
    return 0;
}

int my_sprintf(char *str, const char *format, ...) {
    int d = 0, ii = 0, i = 0, j = 0, flag = 0, result = 0, p = 0, counter = 0;
    double f;
    my_clear(str);
    va_list argptr;
    va_start(argptr, format);
    while(*format != '\0') {
        if (*format != '%') {
            char tmp = *format;
            my_strcat(str, &tmp);
            counter++;
        }
        if (*format == '%') {
            if (!check_string(format, counter)) {
                printf("You haven't entered a qualifier!\n");
                break;
            }
            char token_str[256];
            format++;
            my_parser(format, token_str, &counter);
            start_processing(str, token_str, argptr);
            format+=counter;
            counter = 0;
        }
        format++;
    }
    va_end(argptr);
    return result;
}

void my_reverse_str(char *dest, char *str) {
    my_size_t len = my_strlen(str);
    for (my_size_t i = 0, j = len - 1; i < len; i++, j--) {
        dest[i] = str[j];
    }
}


char *my_itoa(int num) {
    char tmp[20] = {0};
    char *res = (char*) malloc(10 * sizeof(char));
    int i = 0;
    int n = num;
    while (n != 0) {
        if (n < 0) {
            tmp[i] = (n *(-1) % 10) + '0';
        } else {
            tmp[i] = (n % 10) + '0';
        }
        n /= 10;
        i++;
    }
    if (num < 0) {
        tmp[i] = '-';
    }
    my_reverse_str(res, tmp);
    free(res);
    return res;
}

char *my_strcat(char *dest, const char *src) {
    char *t;
    for (t = dest; *t; ++t);
    while (*t++ += *src++);
    return dest;
}

my_size_t my_strlen(const char* str) {
    const char* cur = str;
    for (; *cur; ++cur) {
    }
    return cur - str;
}

void my_clear(char *str) {
    while (*str) {
        *str = 0;
        str++;
    }
}

void my_dtos(char *str, double num, double precision) {
    int m = (log10(num));
    int digit, i = 0;
    char tmp;
    while ((num > 0 + precision) || (m >= 0)) {
        float weight = pow(10.0f, m);
        digit = floor(num / weight);
        num -= (digit*weight);
        tmp = digit + '0';
        str[++i] = tmp;
        //strcat(str, tmp);
        //str[i++] = (digit + '0');
        if (m == 0 && precision != 1) {
            str[++i] = '.';
        }
        m--;
    }
    str[i] = '\0';
}

int get_format_token(char *format, char *token_str) {
    int i = 0;
    while(format) {
        if (check_specs(*format)) {
            break;
        }
        token_str[i] = *format;
        format += 1;
        i += 1;
    }
    token_str[i] = *format;
    token_str[i+1] = '\0';
    return i;
}

int convert_from_int(char *str, int *displace) {
    int num = my_atoi(str);
    int tmp = num;
    while (tmp != 0) {
        tmp = tmp / 10;
        *displace += 1;
    }
    return num;
}

int get_number_length(char *str) {
    int len = 0;
    while ((*str >= '0' && *str <= '9')) {
        len++;
        str += 1;
    }
    return len;
}

int get_hexnum_length(char *str) {
    int len = 0;
    while((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F') || (*str == 'x' || *str == 'X')) {
        len++;
        str += 1;
    }
    return len;
}

int get_octnum_length(char *str) {
    int len = 0;
    while (*str >= '0' && *str <= '7') {
        len++;
        str += 1;
    }
    printf("%s\n", str);
    if (str[0] == '-' && str[1] == '-') {
        len = 0;
    }
    return len;
}

unsigned int convert_from_hex(const char *arr, int len, int *displace, int flag) {
    unsigned int res = 0;
    unsigned int base = 1;
    int numbers = 48, bigletters = 55, smallletters = 87;
    int last = flag ? 1 : 0;
    if (flag != -1) {
    for (int i = len - 1; i >= last; i -= 1) {
        if (arr[i] >= '0' && arr[i] <= '9') {
            res += (arr[i] - numbers) * base;
        } else if (arr[i] >= 'A' && arr[i] <= 'F') {
            res += (arr[i] - bigletters) * base;
        } else if (arr[i] >= 'a' && arr[i] <= 'f') {
            res += (arr[i] - smallletters) * base;
        }
        base *= 16;
    }
    }
    *displace += len;
    return res;
}

unsigned int convert_from_oct(const char *arr, int len, int *displace) {
    unsigned int res = 0;
    unsigned int base = 1;
    int numbers = 48;
    for (int i = len - 1; i >= 0; i -= 1) {
        if (arr[i] >= '0' && arr[i] <= '7') {
            res += (arr[i] - numbers) * base;
            base *= 8;
        }
    }
    *displace += len;
    return res;
}

int my_atoi(const char *s) {
  char *str = (char *)s;
  size_t n = my_strlen(str);
  char tmp[n];
  int res = 0;
  int rank = 0;
  for (int i = 0; i < n; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      tmp[i] = str[i];
      tmp[i + 1] = '\0';
      rank++;
    } else {
      break;
    }
  }
  rank--;
  int counter = 0;
  for (int i = rank; 0 <= i; i--) {
    int num = tmp[i] - '0';
    res = res + (num * expo(10, counter));
    counter++;
  }
  return res;
}

int skip_spaces(const char *str) {
    int displace = 0;
    while (*str == ' ') {
        str += 1;
        displace++;
    }
    return displace;
}

int expo(int k, int n) {
  int b = k;
  if (n == 0) {
    k = 1;
  }
  if (n == 1) {
    k = k;
  }
  while (n > 1) {
    k *= b;
    n--;
  }
  return k;
}

int check_specs(char c) {
    int res = 0;
    char *specs = "cdieEfgGosuxXpn%";
    for (int i = 0; i != 16; i++) {
        if (specs[i] == c) {
            res = 1;
            break;
        }
    }
    return res;
}

int check_string(const char *str, int counter) {
    int res = 0, i = 1;
    while (str[i] != '\0') {
        if (check_specs(str[i])) {
            res = 1;
            break;
        }
        i++;
    }
    return res;
}

int check_int(char c) {
    int res = 0;
    char *specs = "0123456789";
    for (int i = 0; i != 10; i++) {
        if (specs[i] == c) {
            res = 1;
            break;
        }
    }
    return res;
}
