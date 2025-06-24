/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** utils for groupby
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void fill_group(dataframe_t *grouped_df, groupbycontext_t *ctx,
    int group_index)
{
    grouped_df->data[group_index][0] = strdup((char *)ctx->dataframe->
    data[group_index][ctx->aggregate_by_index]);
    if (!grouped_df->data[group_index][0]) {
        return;
    }
    for (int k = 0; k < ctx->nb_to_aggregate; k++) {
        aggregate_values(grouped_df, ctx, group_index, k);
    }
}

static void initialize_grouped_df_types(dataframe_t *grouped_df,
    dataframe_t *dataframe, int aggregate_by_index, int *to_aggregate_indices)
{
    grouped_df->column_types[0] = dataframe->column_types[aggregate_by_index];
    for (int i = 0; i < grouped_df->nb_columns - 1; i++) {
        grouped_df->column_types[1 + i] = dataframe->
        column_types[to_aggregate_indices[i]];
    }
}

static int allocate_grouped_df_rows(dataframe_t *grouped_df)
{
    for (int i = 0; i < grouped_df->nb_rows; i++) {
        grouped_df->data[i] = malloc(sizeof(void *) * grouped_df->nb_columns);
        if (!grouped_df->data[i]) {
            return 0;
        }
    }
    return 1;
}

dataframe_t *initialize_grouped_df(groupbycontext_t *ctx)
{
    dataframe_t *grouped_df = malloc(sizeof(dataframe_t));

    if (!grouped_df) {
        return NULL;
    }
    grouped_df->nb_columns = 1 + ctx->nb_to_aggregate;
    grouped_df->nb_rows = ctx->nb_groups;
    if (!allocate_grouped_df_columns(grouped_df, grouped_df->nb_columns,
        ctx->aggregate_by, ctx->to_aggregate)) {
        df_free(grouped_df);
        return NULL;
    }
    initialize_grouped_df_types(grouped_df, ctx->dataframe,
        ctx->aggregate_by_index, ctx->to_aggregate_indices);
    if (!allocate_grouped_df_rows(grouped_df)) {
        df_free(grouped_df);
        return NULL;
    }
    return grouped_df;
}

int *get_aggregate_indices(dataframe_t *dataframe,
    const char **to_aggregate, int nb_to_aggregate)
{
    int *to_aggregate_indices = malloc(sizeof(int) * nb_to_aggregate);

    if (!to_aggregate_indices) {
        return NULL;
    }
    for (int i = 0; i < nb_to_aggregate; i++) {
        to_aggregate_indices[i] = find_column_index(dataframe,
            to_aggregate[i]);
        if (to_aggregate_indices[i] == -1) {
            free(to_aggregate_indices);
            return NULL;
        }
    }
    return to_aggregate_indices;
}

static int is_value_unique(dataframe_t *dataframe,
    int current_index, int column_index)
{
    for (int j = 0; j < current_index; j++) {
        if (strcmp((char *)dataframe->data[current_index][column_index],
            (char *)dataframe->data[j][column_index]) == 0) {
            return 0;
        }
    }
    return 1;
}

int count_unique_groups(dataframe_t *dataframe, int aggregate_by_index)
{
    int nb_groups = 0;

    for (int i = 0; i < dataframe->nb_rows; i++) {
        if (is_value_unique(dataframe, i, aggregate_by_index)) {
            nb_groups++;
        }
    }
    return nb_groups;
}

static int allocate_dataframe_structures(dataframe_t *grouped_df,
    int nb_columns, int nb_rows)
{
    grouped_df->column_names = malloc(sizeof(char *) * nb_columns);
    grouped_df->column_types = malloc(sizeof(column_type_t) * nb_columns);
    grouped_df->data = malloc(sizeof(void **) * nb_rows);
    if (!grouped_df->column_names ||
        !grouped_df->column_types || !grouped_df->data) {
        return 0;
    }
    return 1;
}

static int initialize_column_names(dataframe_t *grouped_df,
    const char *aggregate_by, const char **to_aggregate, int nb_columns)
{
    grouped_df->column_names[0] = strdup(aggregate_by);
    if (!grouped_df->column_names[0]) {
        return 0;
    }
    for (int i = 0; i < nb_columns - 1; i++) {
        grouped_df->column_names[1 + i] = strdup(to_aggregate[i]);
        if (!grouped_df->column_names[1 + i]) {
            return 0;
        }
    }
    return 1;
}

int allocate_grouped_df_columns(dataframe_t *grouped_df, int nb_columns,
    const char *aggregate_by, const char **to_aggregate)
{
    if (!allocate_dataframe_structures(grouped_df, nb_columns,
        grouped_df->nb_rows)) {
        return 0;
    }
    if (!initialize_column_names(grouped_df, aggregate_by,
        to_aggregate, nb_columns)) {
        return 0;
    }
    return 1;
}
