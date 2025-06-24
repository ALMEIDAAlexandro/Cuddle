/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** sort
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void swap_rows(void **row1, void **row2, int nb_columns)
{
    void *temp;

    for (int i = 0; i < nb_columns; i++) {
        temp = row1[i];
        row1[i] = row2[i];
        row2[i] = temp;
    }
}

static bool should_swap(void *value1, void *value2,
    bool (*sort_func)(void *, void *))
{
    return value1 != NULL && value2 != NULL && sort_func(value1, value2);
}

static void check_and_swap_rows(dataframe_t *dataframe, int j, int col_index,
    bool (*sort_func)(void *, void *))
{
    void *value1 = dataframe->data[j][col_index];
    void *value2 = dataframe->data[j + 1][col_index];

    if (should_swap(value1, value2, sort_func)) {
        swap_rows(dataframe->data[j], dataframe->data[j + 1],
            dataframe->nb_columns);
    }
}

static void sort_dataframe(dataframe_t *dataframe, int col_index,
    bool (*sort_func)(void *, void *))
{
    for (int i = 0; i < dataframe->nb_rows - 1; i++) {
        for (int j = 0; j < dataframe->nb_rows - i - 1; j++) {
            check_and_swap_rows(dataframe, j, col_index, sort_func);
        }
    }
}

static dataframe_t *initialize_dataframe(dataframe_t *original_df)
{
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!df) {
        return NULL;
    }
    df->nb_columns = original_df->nb_columns;
    df->nb_rows = original_df->nb_rows;
    df->column_names = malloc(df->nb_columns * sizeof(char *));
    df->column_types = malloc(df->nb_columns * sizeof(column_type_t));
    df->data = malloc(df->nb_rows * sizeof(void **));
    if (!df->column_names || !df->column_types || !df->data) {
        df_free(df);
        return NULL;
    }
    return df;
}

static void copy_dataframe_contents(dataframe_t *source,
    dataframe_t *destination)
{
    for (int i = 0; i < source->nb_columns; i++) {
        destination->column_names[i] = strdup(source->column_names[i]);
        destination->column_types[i] = source->column_types[i];
    }
    for (int i = 0; i < source->nb_rows; i++) {
        destination->data[i] = malloc(source->nb_columns * sizeof(void *));
        for (int j = 0; j < source->nb_columns; j++) {
            destination->data[i][j] = source->data[i][j];
        }
    }
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *, void *))
{
    dataframe_t *sorted_df;
    int col_index;

    if (!dataframe || !column || !sort_func) {
        return NULL;
    }
    col_index = find_column_index(dataframe, column);
    if (col_index == -1) {
        return NULL;
    }
    sorted_df = initialize_dataframe(dataframe);
    if (!sorted_df) {
        return NULL;
    }
    copy_dataframe_contents(dataframe, sorted_df);
    sort_dataframe(sorted_df, col_index, sort_func);
    sorted_df->separator = dataframe->separator;
    return sorted_df;
}
