/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** groupby
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void aggregate_values(dataframe_t *grouped_df, groupbycontext_t *ctx,
    int group_index, int column_index)
{
    int nb_values = 0;
    void **values = malloc(sizeof(void *) * ctx->dataframe->nb_rows);
    const char *group_value;
    void *result;

    if (!values)
        return;
    group_value = (char *)grouped_df->data[group_index][0];
    for (int l = 0; l < ctx->dataframe->nb_rows; l++) {
        if (strcmp((char *)ctx->dataframe->data[l][ctx->aggregate_by_index],
            group_value) == 0) {
            values[nb_values] = ctx->dataframe->data[l][ctx->
                to_aggregate_indices[column_index]];
                nb_values++;
        }
    }
    result = ctx->agg_func(values, nb_values);
    grouped_df->data[group_index][1 + column_index] = result;
    free(values);
}

static int is_new_group(dataframe_t *grouped_df, groupbycontext_t *ctx,
    int row_index, int group_index)
{
    for (int j = 0; j < group_index; j++) {
        if (strcmp((char *)ctx->dataframe->data[row_index][ctx->
            aggregate_by_index], (char *)grouped_df->data[j][0]) == 0) {
            return 0;
        }
    }
    return 1;
}

static void fill_grouped_df(dataframe_t *grouped_df, groupbycontext_t *ctx)
{
    int group_index = 0;

    for (int i = 0; i < ctx->dataframe->nb_rows; i++) {
        if (is_new_group(grouped_df, ctx, i, group_index)) {
            fill_group(grouped_df, ctx, group_index);
            group_index++;
        }
    }
}

static int validate_arguments(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **, int))
{
    if (!dataframe || !aggregate_by || !to_aggregate || !agg_func) {
        return 0;
    }
    return 1;
}

static int initialize_aggregate_indices(groupbycontext_t *ctx)
{
    ctx->to_aggregate_indices = get_aggregate_indices(ctx->dataframe,
        ctx->to_aggregate, ctx->nb_to_aggregate);
    if (!ctx->to_aggregate_indices) {
        return 0;
    }
    return 1;
}

static int count_unique_groups_in_context(groupbycontext_t *ctx)
{
    ctx->nb_groups = count_unique_groups(ctx->dataframe,
        ctx->aggregate_by_index);
    return 1;
}

static dataframe_t *create_and_fill_grouped_df(groupbycontext_t *ctx)
{
    dataframe_t *grouped_df = initialize_grouped_df(ctx);

    if (!grouped_df) {
        free(ctx->to_aggregate_indices);
        return NULL;
    }
    fill_grouped_df(grouped_df, ctx);
    return grouped_df;
}

static int validate_and_init_context(groupbycontext_t *ctx)
{
    if (!validate_arguments(ctx->dataframe, ctx->aggregate_by,
        ctx->to_aggregate, ctx->agg_func))
        return 0;
    ctx->aggregate_by_index = find_column_index(ctx->dataframe,
        ctx->aggregate_by);
    if (ctx->aggregate_by_index == -1) {
        return 0;
    }
    ctx->nb_to_aggregate = 0;
    while (ctx->to_aggregate[ctx->nb_to_aggregate] != NULL)
        ctx->nb_to_aggregate++;
    return initialize_aggregate_indices(ctx) &&
    count_unique_groups_in_context(ctx);
}

static dataframe_t *create_grouped_df(groupbycontext_t *ctx)
{
    dataframe_t *grouped_df = create_and_fill_grouped_df(ctx);

    free(ctx->to_aggregate_indices);
    return grouped_df;
}

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **, int))
{
    groupbycontext_t ctx = {dataframe, aggregate_by, to_aggregate,
        agg_func, -1, NULL, 0, 0};
    dataframe_t *grouped_df;

    if (!validate_and_init_context(&ctx))
        return NULL;
    grouped_df = create_grouped_df(&ctx);
    if (grouped_df)
        grouped_df->separator = dataframe->separator;
    return grouped_df;
}
