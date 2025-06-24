##
## EPITECH PROJECT, 2025
## Cuddle
## File description:
## Makefile for CUDDLE Library
##

SRC		=	src/df_apply/dataframe_apply.c \
			src/df_describe/dataframe_describe.c \
			src/df_filter/dataframe_filter.c \
			src/df_free/dataframe_free.c \
			src/df_groupby/dataframe_groupby.c \
			src/df_groupby/utils_groupby.c \
			src/df_info/dataframe_info.c \
			src/df_read_csv/dataframe_read.c \
			src/df_shape/dataframe_shape.c \
			src/df_sort/dataframe_sort.c \
			src/df_write_csv/dataframe_write.c \
			src/get_value/dataframe_get_value.c \
			src/get_values/dataframe_get_values.c\
			src/get_unique_values/dataframe_get_unique_values.c\
			src/head/dataframe_head.c \
			src/tail/dataframe_tail.c \
			src/utils/converters/dataframe_conversion.c \
			src/utils/type_detectors/dataframe_type_detection.c \
			src/utils/type_detectors/type_detection.c \
			src/utils/dataframe_utils.c\
			src/to_type/convert_type.c\
			src/to_type/dataframe_to_type.c\

OBJS		=	$(SRC:.c=.o)
NAME		=	libcuddle.a
COMP		=	gcc
FLAGS		=	-Wall -Wextra
INCLUDE		=	-Iinclude -lm

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(COMP) $(FLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
