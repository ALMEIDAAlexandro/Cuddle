/*
** EPITECH PROJECT, 2025
** dataframe_conversion
** File description:
** Functions for converting dataframe data types
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


static void **allocate_row_memory(int nb_columns)
{
    return malloc(nb_columns * sizeof(void *));
}

static void *convert_to_bool(char *value)
{
    int *new_value = malloc(sizeof(int));

    *new_value = (strcmp(value, "true") == 0);
    return new_value;
}

static void *convert_to_int(char *value)
{
    int *new_value = malloc(sizeof(int));

    *new_value = atoi(value);
    return new_value;
}

static void *convert_to_uint(char *value)
{
    unsigned int *new_value = malloc(sizeof(unsigned int));

    *new_value = strtoul(value, NULL, 10);
    return new_value;
}

static void *convert_to_float(char *value)
{
    float *new_value = malloc(sizeof(float));

    *new_value = strtof(value, NULL);
    return new_value;
}

static void *duplicate_string(char *value)
{
    return strdup(value);
}

static void *convert_value(char *value, column_type_t type)
{
    switch (type) {
        case BOOL:
            return convert_to_bool(value);
        case INT:
            return convert_to_int(value);
        case UINT:
            return convert_to_uint(value);
        case FLOAT:
            return convert_to_float(value);
        default:
            return duplicate_string(value);
    }
}

static void free_old_data(void ***data, int nb_rows)
{
    for (int i = 0; i < nb_rows; i++) {
        free(data[i]);
    }
    free(data);
}

void df_convert_data(dataframe_t *df)
{
    void ***new_data = malloc(df->nb_rows * sizeof(void **));
    char *value;

    for (int row = 0; row < df->nb_rows; row++) {
        new_data[row] = allocate_row_memory(df->nb_columns);
        for (int col = 0; col < df->nb_columns; col++) {
            value = (char *)df->data[row][col];
            new_data[row][col] = convert_value(value, df->column_types[col]);
            free(df->data[row][col]);
        }
    }
    free_old_data(df->data, df->nb_rows);
    df->data = new_data;
}
