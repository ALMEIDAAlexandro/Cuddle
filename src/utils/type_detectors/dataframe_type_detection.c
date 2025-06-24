/*
** EPITECH PROJECT, 2025
** dataframe_type_detection_2
** File description:
** Additional functions for detecting column types in dataframe
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_all_values_int(dataframe_t *df, int col)
{
    for (int row = 0; row < df->nb_rows; row++) {
        if (!is_integer((char *)df->data[row][col]))
            return 0;
    }
    return 1;
}

static int is_all_values_uint(dataframe_t *df, int col)
{
    for (int row = 0; row < df->nb_rows; row++) {
        if (!is_unsigned_integer((char *)df->data[row][col]))
            return 0;
    }
    return 1;
}

static int is_all_values_float(dataframe_t *df, int col)
{
    for (int row = 0; row < df->nb_rows; row++) {
        if (!is_float((char *)df->data[row][col]))
            return 0;
    }
    return 1;
}

static int is_all_values_boolean(dataframe_t *df, int col)
{
    for (int row = 0; row < df->nb_rows; row++) {
        if (!is_boolean((char *)df->data[row][col]))
            return 0;
    }
    return 1;
}

void detect_column_type(dataframe_t *df, int col)
{
    df->column_types[col] = UNDEFINED;
    if (is_all_values_boolean(df, col))
        df->column_types[col] = BOOL;
    if (is_all_values_int(df, col))
        df->column_types[col] = INT;
    if (is_all_values_int(df, col) && is_all_values_uint(df, col))
        df->column_types[col] = UINT;
    if (is_all_values_float(df, col))
        df->column_types[col] = FLOAT;
    if (df->column_types[col] == UNDEFINED)
        df->column_types[col] = STRING;
}

void df_detect_column_types(dataframe_t *df)
{
    df->column_types = malloc(df->nb_columns * sizeof(column_type_t));
    for (int col = 0; col < df->nb_columns; col++) {
        detect_column_type(df, col);
    }
}
