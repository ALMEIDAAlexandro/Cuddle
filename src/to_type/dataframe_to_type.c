/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** changes a type to another one
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


static void *convert_value(void *value, column_type_t curr_type,
    column_type_t downcast)
{
    if (!value)
        return NULL;
    switch (downcast) {
        case BOOL:
            return convert_bool(value, curr_type);
        case INT:
            return convert_int(value, curr_type);
        case UINT:
            return convert_uint(value, curr_type);
        case FLOAT:
            return convert_float(value, curr_type);
        case STRING:
            return convert_string(value, curr_type);
        default:
            return NULL;
    }
}

static int get_column_index(dataframe_t *df, const char *column)
{
    for (int i = 0; i < df->nb_columns; i++) {
        if (strcmp(df->column_names[i], column) == 0)
            return i;
    }
    return -1;
}

static dataframe_t *allocate_dataframe(dataframe_t *df)
{
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (!new_df)
        return NULL;
    new_df->nb_rows = df->nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(df->nb_columns * sizeof(char *));
    new_df->column_types = malloc(df->nb_columns * sizeof(column_type_t));
    new_df->data = malloc(df->nb_rows * sizeof(void **));
    if (!new_df->column_names || !new_df->column_types || !new_df->data)
        return df_free(new_df), NULL;
    return new_df;
}

static void copy_column_metadata(dataframe_t *new_df, dataframe_t *df,
    int col_idx, column_type_t downcast)
{
    for (int i = 0; i < df->nb_columns; i++) {
        new_df->column_names[i] = strdup(df->column_names[i]);
        new_df->column_types[i] = df->column_types[i];
    }
    new_df->column_types[col_idx] = downcast;
}

static int copy_dataframe_rows(dataframe_t *new_df, dataframe_t *df,
    int col_idx, column_type_t downcast)
{
    for (int r = 0; r < df->nb_rows; r++) {
        new_df->data[r] = malloc(df->nb_columns * sizeof(void *));
        if (!new_df->data[r])
            return df_free(new_df), 0;
        for (int c = 0; c < df->nb_columns; c++) {
            new_df->data[r][c] = (c == col_idx) ?
                convert_value(df->data[r][c], df->column_types[c], downcast) :
                df->data[r][c];
        }
    }
    return 1;
}

dataframe_t *df_to_type(dataframe_t *df, const char *column,
    column_type_t downcast)
{
    int col_idx;
    dataframe_t *new_df;

    if (!df)
        return NULL;
    col_idx = get_column_index(df, column);
    if (col_idx == -1)
        return NULL;
    new_df = allocate_dataframe(df);
    new_df->separator = df->separator;
    if (!new_df)
        return NULL;
    copy_column_metadata(new_df, df, col_idx, downcast);
    if (!copy_dataframe_rows(new_df, df, col_idx, downcast))
        return NULL;
    return new_df;
}
