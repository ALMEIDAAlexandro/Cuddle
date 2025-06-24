/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe writter in a new csv
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>

static void print_bool_value(FILE *file, int col,
    int row, dataframe_t *dataframe)
{
    fprintf(file, "%s", *(bool *)dataframe->data[row][col] != 0 ?
    "true" : "false");
}

static void print_value(dataframe_t *dataframe, int col, int row,
    FILE *file)
{
    switch (dataframe->column_types[col]) {
        case BOOL:
            print_bool_value(file, col, row, dataframe);
            break;
        case INT:
            fprintf(file, "%d", *(int *)dataframe->data[row][col]);
            break;
        case UINT:
            fprintf(file, "%u", *(unsigned int *)dataframe->data[row][col]);
            break;
        case FLOAT:
            fprintf(file, "%.2f", *(float *)dataframe->data[row][col]);
            break;
        case STRING:
            fprintf(file, "%s", (char *)dataframe->data[row][col]);
            break;
        default:
            fprintf(file, "UNKNOWN");
            break;
    }
}

static void print_write_datas(dataframe_t *dataframe, int col, int row,
    FILE *file)
{
    print_value(dataframe, col, row, file);
    if (col < dataframe->nb_columns - 1)
        fprintf(file, "%s", dataframe->separator);
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (!file || !dataframe) {
        return 84;
    }
    for (int col = 0; col < dataframe->nb_columns; col++) {
        fprintf(file, "%s", dataframe->column_names[col]);
        if (col < dataframe->nb_columns - 1) {
            fprintf(file, "%s", dataframe->separator);
        }
    }
    fprintf(file, "\n");
    for (int row = 0; row < dataframe->nb_rows; row++) {
        for (int col = 0; col < dataframe->nb_columns; col++)
            print_write_datas(dataframe, col, row, file);
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}
