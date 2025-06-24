/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** return a dataframe_t head, the nbrows first lines of the file
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dataframe_t *df_head_init(dataframe_t *df, int nbrows)
{
    dataframe_t *head = df_init_dataframe(df->separator);

    if (!head)
        return NULL;
    head->nb_columns = df->nb_columns;
    head->nb_rows = nbrows;
    head->column_names = malloc(head->nb_columns * sizeof(char *));
    head->column_types = malloc(head->nb_columns * sizeof(column_type_t));
    if (!head->column_names || !head->column_types)
        return df_free(head), NULL;
    return head;
}

static int df_head_copy_metadata(dataframe_t *df, dataframe_t *head)
{
    for (int col = 0; col < head->nb_columns; col++) {
        head->column_names[col] = strdup(df->column_names[col]);
        if (!head->column_names[col])
            return df_free(head), -1;
    }
    memcpy(head->column_types, df->column_types,
        head->nb_columns * sizeof(column_type_t));
    return 0;
}

static int df_head_allocate_rows(dataframe_t *head)
{
    head->data = malloc(head->nb_rows * sizeof(void **));
    if (!head->data)
        return df_free(head), -1;
    for (int row = 0; row < head->nb_rows; row++) {
        head->data[row] = malloc(head->nb_columns * sizeof(void *));
        if (!head->data[row])
            return df_free(head), -1;
    }
    return 0;
}

static int df_head_copy_cell(void *src, void **dest, column_type_t type)
{
    if (type == STRING) {
        *dest = strdup((char *)src);
    } else {
        *dest = malloc(sizeof(int));
        if (*dest)
            memcpy(*dest, src, sizeof(int));
    }
    return *dest ? 0 : -1;
}

static int df_head_copy_row(dataframe_t *df, dataframe_t *head, int row)
{
    for (int col = 0; col < head->nb_columns; col++) {
        if (df_head_copy_cell(df->data[row][col], &head->data[row][col],
            df->column_types[col]) < 0)
            return df_free(head), -1;
    }
    return 0;
}

static int df_head_copy_data(dataframe_t *df, dataframe_t *head)
{
    if (df_head_allocate_rows(head) < 0)
        return -1;
    for (int row = 0; row < head->nb_rows; row++) {
        if (df_head_copy_row(df, head, row) < 0)
            return -1;
    }
    return 0;
}

dataframe_t *df_head(dataframe_t *df, int nbrows)
{
    dataframe_t *head;

    if (!df || nbrows <= 0)
        return NULL;
    if (nbrows > df->nb_rows)
        nbrows = df->nb_rows;
    head = df_head_init(df, nbrows);
    if (!(head))
        return NULL;
    if (df_head_copy_metadata(df, head) < 0)
        return NULL;
    if (df_head_copy_data(df, head) < 0)
        return NULL;
    return head;
}
