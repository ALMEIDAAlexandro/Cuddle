/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** print all of the values of an asked column
*/

#include "dataframe.h"
#include <string.h>
#include <stdlib.h>

int get_column_index(dataframe_t *dataframe, const char *column)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0) {
            return i;
        }
    }
    return -1;
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int column_index;
    void **values;

    if (!dataframe || !column)
        return NULL;
    column_index = get_column_index(dataframe, column);
    values = malloc((dataframe->nb_rows + 1) * sizeof(void *));
    if (column_index == -1) {
        return NULL;
    }
    if (values == NULL) {
        return NULL;
    }
    for (int i = 0; i < dataframe->nb_rows; i++) {
        values[i] = dataframe->data[i][column_index];
    }
    values[dataframe->nb_rows] = NULL;
    return values;
}
