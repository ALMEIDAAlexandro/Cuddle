/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** print all of the information about the types of the columns
*/

#include "dataframe.h"
#include <stdio.h>

static const char *get_column_type_str(int column_type)
{
    switch (column_type) {
        case BOOL:
        return "bool";
        case INT:
        return "int";
        case UINT:
        return "unsigned int";
        case FLOAT:
        return "float";
        case STRING:
        return "string";
        case UNDEFINED:
        return "undefined";
        default:
        return "unknown";
    }
}

void df_info(dataframe_t *df)
{
    int i;

    if (!df)
        return;
    printf("%d columns:\n", df->nb_columns);
    for (i = 0; i < df->nb_columns; i++) {
        printf("- %s: %s\n", df->column_names[i],
        get_column_type_str(df->column_types[i]));
    }
}
