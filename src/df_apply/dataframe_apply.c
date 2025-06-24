/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** apply
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static dataframe_t *initialize_new_dataframe(dataframe_t *original_df)
{
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (!new_df) {
        return NULL;
    }
    new_df->nb_columns = original_df->nb_columns;
    new_df->nb_rows = original_df->nb_rows;
    new_df->column_names = malloc(sizeof(char *) * new_df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * new_df->nb_columns);
    new_df->data = malloc(sizeof(void **) * new_df->nb_rows);
    if (!new_df->column_names || !new_df->column_types || !new_df->data) {
        df_free(new_df);
        return NULL;
    }
    return new_df;
}

static bool copy_column_structures(dataframe_t *source_df,
    dataframe_t *dest_df)
{
    for (int i = 0; i < source_df->nb_columns; i++) {
        dest_df->column_names[i] = strdup(source_df->column_names[i]);
        if (!dest_df->column_names[i]) {
            return false;
        }
        dest_df->column_types[i] = source_df->column_types[i];
    }
    return true;
}

static bool initialize_and_transform_row(dataframe_t *dataframe,
    dataframe_t *applied_df, int col_index, void *(*apply_func)(void *))
{
    for (int i = 0; i < applied_df->nb_rows; i++) {
        applied_df->data[i] = malloc(sizeof(void *) * applied_df->nb_columns);
        if (!applied_df->data[i]) {
            return false;
        }
        for (int j = 0; j < applied_df->nb_columns; j++) {
            applied_df->data[i][j] = (j == col_index) ?
            apply_func(dataframe->data[i][j]) : dataframe->data[i][j];
        }
    }
    return true;
}

static bool validate_arguments(dataframe_t *df, const char *column,
    void *(*apply_func)(void *))
{
    if (!df || !column || !apply_func) {
        return false;
    }
    return true;
}

dataframe_t *setup_and_validate_dataframe(dataframe_t *dataframe,
    const char *column)
{
    int column_index = find_column_index(dataframe, column);
    dataframe_t *applied_df;

    if (column_index == -1) {
        return NULL;
    }
    applied_df = initialize_new_dataframe(dataframe);
    if (!applied_df)
        return NULL;
    if (!copy_column_structures(dataframe, applied_df)) {
        df_free(applied_df);
        return NULL;
    }
    return applied_df;
}

bool apply_transformations(dataframe_t *dataframe, dataframe_t *applied_df,
    int column_index, void *(*apply_func)(void *))
{
    if (!initialize_and_transform_row(dataframe, applied_df,
        column_index, apply_func)) {
        df_free(applied_df);
        return false;
    }
    return true;
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *))
{
    dataframe_t *applied_df;
    int column_index;

    if (!validate_arguments(dataframe, column, apply_func))
        return NULL;
    applied_df = setup_and_validate_dataframe(dataframe, column);
    if (!applied_df)
        return NULL;
    column_index = find_column_index(dataframe, column);
    if (!apply_transformations(dataframe, applied_df, column_index,
        apply_func)) {
        return NULL;
    }
    applied_df->separator = dataframe->separator;
    return applied_df;
}
