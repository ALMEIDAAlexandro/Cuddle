/*
** EPITECH PROJECT, 2025
** dataframe_type_detection
** File description:
** Functions for detecting column types in dataframe
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_integer(const char *str)
{
    int i = 0;

    if (str[0] == '-' || str[0] == '+')
        i++;
    for (; str[i]; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

int is_unsigned_integer(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

static int is_digit_or_dot(char ch)
{
    return isdigit(ch) || ch == '.';
}

static int increment_dot_count(int *dot_count)
{
    (*dot_count)++;
    if (*dot_count > 1)
        return -1;
    return 0;
}

static int count_dots(const char *str)
{
    int dot_count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '.' && increment_dot_count(&dot_count) == -1)
            return -1;
    }
    return dot_count;
}

int is_float(const char *str)
{
    int start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    int dot_count;

    for (int i = start; str[i]; i++) {
        if (!is_digit_or_dot(str[i]))
            return 0;
    }
    dot_count = count_dots(str + start);
    return dot_count == 1;
}

int is_boolean(const char *str)
{
    return (strcmp(str, "true") == 0 || strcmp(str, "false") == 0);
}
