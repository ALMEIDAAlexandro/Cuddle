/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** describe
*/

#include "dataframe.h"
#include <stdio.h>
#include "limits.h"
#include <math.h>
#include <float.h>

static int calculate_count(void **data, int size)
{
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (data[i] != NULL)
            count++;
    }
    return count;
}

static double get_value(void *data, column_type_t type)
{
    if (!data)
        return 0;
    switch (type) {
        case INT:
            return *(int *)data;
        case UINT:
            return *(unsigned int *)data;
        case FLOAT:
            return *(float *)data;
        default:
            return 0;
    }
}

static double calculate_mean(void **data, int size, column_type_t type)
{
    double sum = 0;
    double value;
    int count = 0;

    for (int i = 0; i < size; i++) {
        value = get_value(data[i], type);
        sum += value;
        if (data[i] != NULL)
            count++;
    }
    return count > 0 ? sum / count : 0;
}

static double calculate_std(void **data, int size,
    double mean, column_type_t type)
{
    double sum_sq_diff = 0;
    double value;
    double diff;
    int count = 0;

    for (int i = 0; i < size; i++) {
        value = get_value(data[i], type);
        diff = value - mean;
        sum_sq_diff += diff * diff;
        if (data[i] != NULL)
            count++;
    }
    return count > 0 ? sqrt(sum_sq_diff / count) : 0;
}

static double calculate_min(void **data, int size, column_type_t type)
{
    double min = DBL_MAX;
    double value;

    for (int i = 0; i < size; i++) {
        value = get_value(data[i], type);
        if (data[i] != NULL && value < min) {
            min = value;
        }
    }
    return min;
}

static double calculate_max(void **data, int size, column_type_t type)
{
    double max = DBL_MIN;
    double value;

    for (int i = 0; i < size; i++) {
        value = get_value(data[i], type);
        if (data[i] != NULL && value > max) {
            max = value;
        }
    }
    return max;
}

void df_describe_column(void **data, int size,
    const char *column_name, column_type_t type)
{
    int count = calculate_count(data, size);
    double mean = calculate_mean(data, size, type);
    double std = calculate_std(data, size, mean, type);
    double min = calculate_min(data, size, type);
    double max = calculate_max(data, size, type);

    printf("Column: %s\n", column_name);
    printf("Count: %d\n", count);
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", std);
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
}

void process_column(dataframe_t *dataframe, int i)
{
    int row;
    void *column_data[dataframe->nb_rows];

    if (dataframe->column_types[i] == INT ||
        dataframe->column_types[i] == UINT ||
        dataframe->column_types[i] == FLOAT) {
        for (row = 0; row < dataframe->nb_rows; row++) {
            column_data[row] = dataframe->data[row][i];
        }
        df_describe_column(column_data, dataframe->nb_rows,
            dataframe->column_names[i], dataframe->column_types[i]);
    }
}

void df_describe(dataframe_t *dataframe)
{
    int i;

    if (!dataframe) {
        return;
    }
    for (i = 0; i < dataframe->nb_columns; i++) {
        process_column(dataframe, i);
    }
}
