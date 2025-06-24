/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** return a dataframe_t tail, the nbrows last lines of the file
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dataframe_t *df_tail_init(dataframe_t *df, int nbrows)
{
    dataframe_t *tail = df_init_dataframe(df->separator);

    if (!tail)
        return NULL;
    tail->nb_columns = df->nb_columns;
    tail->nb_rows = nbrows;
    tail->column_names = malloc(tail->nb_columns * sizeof(char *));
    tail->column_types = malloc(tail->nb_columns * sizeof(column_type_t));
    if (!tail->column_names || !tail->column_types)
        return df_free(tail), NULL;
    return tail;
}

static int df_tail_copy_metadata(dataframe_t *df, dataframe_t *tail)
{
    for (int col = 0; col < tail->nb_columns; col++) {
        tail->column_names[col] = strdup(df->column_names[col]);
        if (!tail->column_names[col])
            return df_free(tail), -1;
    }
    memcpy(tail->column_types, df->column_types,
        tail->nb_columns * sizeof(column_type_t));
    return 0;
}

static int df_tail_allocate_rows(dataframe_t *tail)
{
    tail->data = malloc(tail->nb_rows * sizeof(void **));
    if (!tail->data)
        return df_free(tail), -1;
    for (int row = 0; row < tail->nb_rows; row++) {
        tail->data[row] = malloc(tail->nb_columns * sizeof(void *));
        if (!tail->data[row])
            return df_free(tail), -1;
    }
    return 0;
}

static int df_tail_copy_cell(void *src, void **dest, column_type_t type)
{
    if (type == STRING) {
        *dest = strdup((char *)src);
    } else {
        *dest = malloc(sizeof(int));
        if (*dest)
            memcpy(*dest, src, sizeof(int));
    }
    return (*dest) ? 0 : -1;
}

static int df_tail_copy_row(dataframe_t *df, dataframe_t *tail, int row)
{
    int src_row = df->nb_rows - tail->nb_rows + row;

    for (int col = 0; col < tail->nb_columns; col++) {
        if (df_tail_copy_cell(df->data[src_row][col], &tail->data[row][col],
            df->column_types[col]) < 0)
            return df_free(tail), -1;
    }
    return 0;
}

static int df_tail_copy_data(dataframe_t *df, dataframe_t *tail)
{
    if (df_tail_allocate_rows(tail) < 0)
        return -1;
    for (int row = 0; row < tail->nb_rows; row++) {
        if (df_tail_copy_row(df, tail, row) < 0)
            return -1;
    }
    return 0;
}

dataframe_t *df_tail(dataframe_t *df, int nbrows)
{
    dataframe_t *tail;

    if (!df || nbrows <= 0)
        return NULL;
    if (nbrows > df->nb_rows)
        nbrows = df->nb_rows;
    tail = df_tail_init(df, nbrows);
    if (!(tail))
        return NULL;
    if (df_tail_copy_metadata(df, tail) < 0)
        return NULL;
    if (df_tail_copy_data(df, tail) < 0)
        return NULL;
    return tail;
}
