/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** returns the value to the index of line and column specified
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *check_is_ok(dataframe_t *dataframe, int row)
{
    if (!dataframe || !dataframe->column_names || !dataframe->data) {
        return NULL;
    }
    if (row < 0 || row >= dataframe->nb_rows) {
        return NULL;
    }
    return (void *)1;
}

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int col_index = -1;

    if (check_is_ok(dataframe, row) == NULL)
        return NULL;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0) {
            col_index = i;
            break;
        }
    }
    if (col_index == -1) {
        return NULL;
    }
    return dataframe->data[row][col_index];
}
