/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** filter
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int find_column_index(dataframe_t *df, const char *column)
{
    for (int i = 0; i < df->nb_columns; i++) {
        if (strcmp(df->column_names[i], column) == 0) {
            return i;
        }
    }
    return -1;
}

static int count_filtered_rows(dataframe_t *df, int col_index,
    bool (*filter_func)(void *))
{
    int count = 0;

    for (int i = 0; i < df->nb_rows; i++) {
        if (df->data[i][col_index] != NULL &&
            filter_func(df->data[i][col_index])) {
            count++;
        }
    }
    return count;
}

static int copy_column_names(dataframe_t *src_df, dataframe_t *dest_df)
{
    for (int i = 0; i < src_df->nb_columns; i++) {
        dest_df->column_names[i] = strdup(src_df->column_names[i]);
        if (!dest_df->column_names[i]) {
            return -1;
        }
    }
    return 0;
}

static void copy_column_types(dataframe_t *src_df, dataframe_t *dest_df)
{
    for (int i = 0; i < src_df->nb_columns; i++) {
        dest_df->column_types[i] = src_df->column_types[i];
    }
}

static int allocate_dataframe_structures(dataframe_t *df,
    int nb_columns, int nb_rows)
{
    df->column_names = malloc(sizeof(char *) * nb_columns);
    df->column_types = malloc(sizeof(column_type_t) * nb_columns);
    df->data = malloc(sizeof(void **) * nb_rows);
    if (!df->column_names || !df->column_types || !df->data) {
        if (df->column_names)
            free(df->column_names);
        if (df->column_types)
            free(df->column_types);
        if (df->data)
            free(df->data);
        return -1;
    }
    return 0;
}

static dataframe_t *initialize_filtered_df(dataframe_t *df,
    int filtered_row_count)
{
    dataframe_t *filtered_df = malloc(sizeof(dataframe_t));

    if (!filtered_df) {
        return NULL;
    }
    filtered_df->nb_columns = df->nb_columns;
    filtered_df->nb_rows = filtered_row_count;
    if (allocate_dataframe_structures(filtered_df, filtered_df->nb_columns,
        filtered_df->nb_rows) == -1) {
        free(filtered_df);
        return NULL;
    }
    if (copy_column_names(df, filtered_df) == -1) {
        df_free(filtered_df);
        return NULL;
    }
    copy_column_types(df, filtered_df);
    return filtered_df;
}

static void allocate_and_copy_row(void ***filtered_data, int row_index,
    void **source_row, int nb_columns)
{
    filtered_data[row_index] = malloc(sizeof(void *) * nb_columns);
    if (!filtered_data[row_index]) {
        return;
    }
    for (int j = 0; j < nb_columns; j++) {
        filtered_data[row_index][j] = source_row[j];
    }
    return;
}

static void fill_filtered_data(dataframe_t *df, dataframe_t *filtered_df,
    int col_index, bool (*filter_func)(void *))
{
    int filtered_row_index = 0;

    for (int i = 0; i < df->nb_rows; i++) {
        if (df->data[i][col_index] != NULL &&
            filter_func(df->data[i][col_index])) {
            allocate_and_copy_row(filtered_df->data,
                filtered_row_index, df->data[i], df->nb_columns);
            filtered_row_index++;
        }
    }
}

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value))
{
    int col_index;
    int filtered_row_count;
    dataframe_t *filtered_df;

    if (!dataframe || !column || !filter_func) {
        return NULL;
    }
    col_index = find_column_index(dataframe, column);
    if (col_index == -1)
        return NULL;
    filtered_row_count = count_filtered_rows(dataframe,
        col_index, filter_func);
    filtered_df = initialize_filtered_df(dataframe, filtered_row_count);
    if (!filtered_df)
        return NULL;
    filtered_df->separator = dataframe->separator;
    fill_filtered_data(dataframe, filtered_df, col_index, filter_func);
    return filtered_df;
}
