/*
** EPITECH PROJECT, 2025
** dataframe_utils
** File description:
** Utility functions for dataframe
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *trim_space(char *str)
{
    size_t len;

    while (*str == ' ' || *str == '\t' ||
        *str == '\n' || *str == '\r')
        str++;
    len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' ||
        str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
    return str;
}

void append_column_name(dataframe_t *df, char *name)
{
    df->column_names = realloc(df->column_names,
        (df->nb_columns + 1) * sizeof(char *));
    df->column_names[df->nb_columns] = strdup(name);
    df->nb_columns++;
}

void df_read_header(FILE *file, dataframe_t *df, const char *separator)
{
    char line[MAX_LINE_LENGTH];

    if (!fgets(line, sizeof(line), file))
        return;
    for (char *token = strtok(line, separator);
        token; token = strtok(NULL, separator)) {
        token = trim_space(token);
        append_column_name(df, token);
    }
}

void df_read_row(char *line, dataframe_t *df, const char *separator)
{
    size_t len = strlen(line);
    char *token;
    int col = 0;

    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    token = strtok(line, separator);
    df->nb_rows++;
    df->data = realloc(df->data, df->nb_rows * sizeof(void **));
    df->data[df->nb_rows - 1] = malloc(df->nb_columns * sizeof(char *));
    while (token && col < df->nb_columns) {
        df->data[df->nb_rows - 1][col] = strdup(token);
        token = strtok(NULL, separator);
        col++;
    }
}
