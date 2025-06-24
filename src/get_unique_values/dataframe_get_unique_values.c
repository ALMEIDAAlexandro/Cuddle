/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** print all of the values one time of an asked column
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool value_exists(void **array, int size,
    void *value, column_type_t type)
{
    for (int i = 0; i < size; i++) {
        if ((type == BOOL || type == INT) && *(int *)array[i] == *(int *)value)
            return true;
        if (type == UINT &&
            *(unsigned int *)array[i] == *(unsigned int *)value)
            return true;
        if (type == FLOAT && *(float *)array[i] == *(float *)value)
            return true;
        if (type == STRING && strcmp((char *)array[i], (char *)value) == 0)
            return true;
    }
    return false;
}

static int get_column_index(dataframe_t *dataframe, const char *column)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0)
            return i;
    }
    return -1;
}

static void **allocate_unique_values(int size)
{
    return malloc(size * sizeof(void *));
}

static void **initialize_unique_values(int size, void **values)
{
    void **unique_values = allocate_unique_values(size);

    if (unique_values == NULL)
        free(values);
    return unique_values;
}

static void process_unique_values(void **unique_values, void **values,
    dataframe_t *dataframe, int *unique_count)
{
    column_type_t column_type = dataframe->column_types[*unique_count];

    for (int i = 0; i < dataframe->nb_rows; i++) {
        if (!value_exists(unique_values, *unique_count,
            values[i], column_type)) {
            unique_values[*unique_count] = values[i];
            (*unique_count)++;
        }
    }
}

static void **finalize_unique_values(void **unique_values, void **values,
    int unique_count)
{
    void **temp = realloc(unique_values, (unique_count + 1) * sizeof(void *));

    if (temp == NULL) {
        free(values);
        return NULL;
    }
    temp[unique_count] = NULL;
    free(values);
    return temp;
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    void **values;
    void **unique_values;
    int column_index;
    int unique_count = 0;

    if (dataframe == NULL || column == NULL)
        return NULL;
    values = df_get_values(dataframe, column);
    if (values == NULL)
        return NULL;
    column_index = get_column_index(dataframe, column);
    if (column_index == -1) {
        free(values);
        return NULL;
    }
    unique_values = initialize_unique_values(dataframe->nb_rows, values);
    if (unique_values == NULL)
        return NULL;
    process_unique_values(unique_values, values, dataframe, &unique_count);
    return finalize_unique_values(unique_values, values, unique_count);
}
