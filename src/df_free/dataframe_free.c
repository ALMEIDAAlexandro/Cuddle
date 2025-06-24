/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** free all of the dataframe_t memory
*/

#include "dataframe.h"
#include <stdlib.h>

void df_free(dataframe_t *df)
{
    if (!df)
        return;
    for (int i = 0; i < df->nb_rows; i++) {
        for (int j = 0; j < df->nb_columns; j++)
            free(df->data[i][j]);
        free(df->data[i]);
    }
    for (int i = 0; i < df->nb_columns; i++)
        free(df->column_names[i]);
    free(df->column_names);
    free(df->column_types);
    free(df->data);
    free(df);
}
