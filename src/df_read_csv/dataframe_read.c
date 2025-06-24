/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** read and write in dataframe_t all the information in csv
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dataframe_t *df_init_dataframe(const char *separator)
{
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!df)
        return NULL;
    df->nb_rows = 0;
    df->nb_columns = 0;
    df->column_names = NULL;
    df->column_types = NULL;
    df->data = NULL;
    df->separator = separator;
    return df;
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    FILE *file = fopen(filename, "r");
    dataframe_t *df;
    char line[MAX_LINE_LENGTH];

    if (!separator)
        separator = ",";
    if (!file)
        return NULL;
    df = df_init_dataframe(separator);
    if (!df)
        return NULL;
    df_read_header(file, df, separator);
    while (fgets(line, sizeof(line), file))
        df_read_row(line, df, separator);
    fclose(file);
    df_detect_column_types(df);
    df_convert_data(df);
    return df;
}
