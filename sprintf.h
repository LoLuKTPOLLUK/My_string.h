#ifndef _SPRINTF_H_
#define _SPRINTF_H_

typedef unsigned s21_size_t;

struct Token {
    int flag;
    int width;
    int precision;
    int length;
    int star;
} Token;

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define FORMAT_MAX 100
#define SPECS_LEN 16
#define FLAGS_LEN 5
#define WIDTH_PRES_LEN 12
#define LENGTH_LEN 3

s21_size_t s21_strlen(const char *str);
int get_format_token(char *format, char *token_str);
int s21_sprintf(char *str, const char *format, ...);
int start_processing(char *str, char*format, va_list params);
int read_int_d(char *str, char *format, va_list parameters);
int read_int_i(char *str, char *format, va_list parameters);
int read_int_x(char *str, char *format, va_list params);
int read_int_o(char *str, char *format, va_list params);
int convert_from_int(char *str, int *displace);
int check_specs(char c);
//int check_flags(char c);
int check_length(char c);
int skip_spaces(const char *str);
int get_format_len(const char **format_str);
int get_number_length(char *str);
int get_hexnum_length(char *str);
int get_octnum_length(char *str);
int expo(int k, int n);
int s21_atoi(const char *s);
unsigned int convert_to_dec(const char *arr, int len, char ch);
unsigned int convert_from_oct(const char *arr, int len, int *displace);
unsigned int convert_from_hex(const char *arr, int len, int *displace, int flag);
void read_symbols(const char **str, char * curr_c, va_list parameters, int *length);
void read_str(const char **str, va_list parameters, int *length);
void init_specs(char *specs);
void init_flags(char *flags);
void init_length(char *length);
void check_parameters(char c, char prev);
void char_cmp(char *arr, char c, int len, int *res);
void* copy_string(char *dest, const char **format_str);
char *get_array_numbers(const char**str, char*curr_c);

#endif /*_SPRINTF_H_*/
