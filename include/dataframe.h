/*
** EPITECH PROJECT, 2025
** tatata
** File description:
** tatata
*/

#ifndef DATAFRAME_H
    #define DATAFRAME_H

    #include <stdio.h>
    #include <stdbool.h>
    #define MAX_LINE_LENGTH 1024

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_types;
    void ***data;
    const char *separator;
} dataframe_t;

typedef struct {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;


typedef struct {
    dataframe_t *dataframe;
    const char *aggregate_by;
    const char **to_aggregate;
    void *(*agg_func)(void **, int);
    int aggregate_by_index;
    int *to_aggregate_indices;
    int nb_to_aggregate;
    int nb_groups;
} groupbycontext_t;


/*
** Fonctions demandées
*/

/*
** Lecture et écriture de fichiers CSV
*/

dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);

/*
** Manipulation de base des données
*/

dataframe_t *df_head(dataframe_t *dataframe, int nbrows);
dataframe_t *df_tail(dataframe_t *df, int nbrows);
void df_info(dataframe_t *df);
dataframe_shape_t df_shape(dataframe_t *df);
void df_describe(dataframe_t *dataframe);

/*
** Filtrage
*/

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value));

/*
** Tri
*/

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *, void *));

/*
** Agrégation
*/

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **, int));

/*
** Transformation
*/

dataframe_t *df_apply(dataframe_t *dataframe,
    const char *column, void *(*apply_func)(void *));
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast);

/*
** Accès aux données
*/

void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);

/*
** Gestion de la mémoire
*/

void df_free(dataframe_t *df);

/*
** Fonctions utilitaires
*/

int allocate_grouped_df_columns(dataframe_t *grouped_df, int nb_columns,
    const char *aggregate_by, const char **to_aggregate);
int count_unique_groups(dataframe_t *dataframe, int aggregate_by_index);
int *get_aggregate_indices(dataframe_t *dataframe,
    const char **to_aggregate, int nb_to_aggregate);
dataframe_t *initialize_grouped_df(groupbycontext_t *ctx);
void fill_group(dataframe_t *grouped_df, groupbycontext_t *ctx,
    int group_index);
void aggregate_values(dataframe_t *grouped_df, groupbycontext_t *ctx,
    int group_index, int column_index);



int find_column_index(dataframe_t *df, const char *column);




dataframe_t *df_init_dataframe(const char *separator);
void df_read_header(FILE *file, dataframe_t *df, const char *separator);
void df_read_row(char *line, dataframe_t *df, const char *separator);
void df_detect_column_types(dataframe_t *df);
void df_convert_data(dataframe_t *df);
int is_float(const char *str);
int is_boolean(const char *str);
int is_integer(const char *str);
int is_unsigned_integer(const char *str);

void *convert_bool(void *value, column_type_t current_type);
void *convert_int(void *value, column_type_t current_type);
void *convert_uint(void *value, column_type_t current_type);
void *convert_float(void *value, column_type_t current_type);
void *convert_string(void *value, column_type_t current_type);

#endif
