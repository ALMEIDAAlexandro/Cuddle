/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** converters for to_type
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void *convert_bool(void *value, column_type_t current_type)
{
    int *bool_value = malloc(sizeof(int));

    if (!bool_value)
        return NULL;
    if (current_type == STRING)
        *bool_value = (strcasecmp((char *)value, "true") == 0 ||
        strcmp((char *)value, "1") == 0);
    if (current_type == FLOAT)
        *bool_value = (*(float *)value != 0.0f);
    if (current_type == UINT)
        *bool_value = (*(unsigned int *)value != 0);
    if (current_type == INT)
        *bool_value = (*(int *)value != 0);
    return bool_value;
}

void *convert_int(void *value, column_type_t current_type)
{
    int *int_value = malloc(sizeof(int));

    if (!int_value)
        return NULL;
    if (current_type == STRING)
        *int_value = atoi((char *)value);
    if (current_type == FLOAT)
        *int_value = (int)(*(float *)value);
    if (current_type == UINT)
        *int_value = (int)(*(unsigned int *)value);
    if (current_type == INT)
        *int_value = *(int *)value;
    return int_value;
}

void *convert_uint(void *value, column_type_t current_type)
{
    unsigned int *uint_value = malloc(sizeof(unsigned int));
    int temp;

    if (!uint_value)
        return NULL;
    if (current_type == STRING){
        temp = atoi((char *)value);
        *uint_value = (temp < 0) ? 0 : (unsigned int)temp;
    }
    if (current_type == FLOAT)
        *uint_value = (unsigned int)(*(float *)value);
    if (current_type == INT)
        *uint_value = (unsigned int)(*(int *)value < 0 ? 0 : *(int *)value);
    if (current_type == UINT)
        *uint_value = *(unsigned int *)value;
    return uint_value;
}

void *convert_float(void *value, column_type_t current_type)
{
    float *float_value = malloc(sizeof(float));

    if (!float_value)
        return NULL;
    if (current_type == STRING)
        *float_value = atof((char *)value);
    if (current_type == UINT)
        *float_value = (float)(*(unsigned int *)value);
    if (current_type == INT)
        *float_value = (float)(*(int *)value);
    if (current_type == FLOAT)
        *float_value = *(float *)value;
    return float_value;
}

static char *allocate_string(void)
{
    char *str_value = malloc(1028);

    if (!str_value)
        return NULL;
    return str_value;
}

static void format_numeric(char *str_value, void *value, column_type_t type)
{
    switch (type) {
        case BOOL:
            snprintf(str_value, 64, "%s", *(int *)value ? "true" : "false");
            break;
        case INT:
            snprintf(str_value, 64, "%d", *(int *)value);
            break;
        case UINT:
            snprintf(str_value, 64, "%u", *(unsigned int *)value);
            break;
        case FLOAT:
            snprintf(str_value, 64, "%.2f", *(float *)value);
            break;
        default:
            break;
    }
}

void *convert_string(void *value, column_type_t current_type)
{
    char *str_value;

    if (current_type == STRING)
        return strdup((char *)value);
    str_value = allocate_string();
    if (!str_value)
        return NULL;
    format_numeric(str_value, value, current_type);
    return str_value;
}
