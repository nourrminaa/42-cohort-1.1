# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#              #
#    Updated: 2026/01/25 19:39:31 by nmina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = push_swap.c \
	  flag-parser/bench.c \
	  flag-parser/get-flag.c \
	  multiple-args-parser/argv-parser.c \
	  parser-helpers/argv-parser-helpers-1.c \
	  parser-helpers/argv-parser-helpers-2.c \
	  stack-utils/ft_split.c \
	  stack-utils/validation-1.c \
	  stack-utils/validation-2.c \
	  stack-utils/ft_split_utils.c \
	  algorithms/small_sort.c \
	  algorithms/small_sort1.c \
	  push-swap-language/instructions.c \
	  push-swap-language/instructions_double.c \
	  push-swap-language/operations.c \
	  push-swap-language/operations_double.c \
	  stack-utils/utils.c \
	  stack-utils/operation-helpers.c \
	  algorithms/algorithm-helpers.c \
	  algorithms/adaptive-algo.c \
	  algorithms/bucket-sort.c \
	  algorithms/insertion-sort.c \
	  algorithms/quick-sort.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
