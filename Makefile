# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by jmoucade          #+#    #+#              #
#    Updated: 2017/04/27 17:14:50 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INC_PATH = includes
SRC_PATH = srcs
LIB_PATH = libft
LIB_INC_PATH = $(LIB_PATH)/includes
LIB = libft/libft.a

SRC =	$(SRC_PATH)/main.c			\
		$(SRC_PATH)/hand_args.c		\
		$(SRC_PATH)/gest_in.c		\
		$(SRC_PATH)/buff_handle.c	\
		$(SRC_PATH)/gest_key.c		\
		$(SRC_PATH)/gest_key2.c		\
		$(SRC_PATH)/deletion.c		\
		$(SRC_PATH)/print_args.c	\
		$(SRC_PATH)/extra.c			\
		$(SRC_PATH)/error.c			\
		$(SRC_PATH)/search.c		\
		$(SRC_PATH)/check_winsize.c	\
		$(SRC_PATH)/calc_colline.c

OSRC = $(SRC:.c=.o)

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
DEL_COLOR=\x1b[33m

all: $(NAME)

$(NAME): $(LIB) $(OSRC)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OSRC) -o $@ -L $(LIB_PATH) -lft -lcurses
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIB_INC_PATH) -I $(INC_PATH) -c -o $@ $?
	@echo "Linking file $@"

clean:
	@make -C libft clean
	@/bin/rm -f $(OSRC)
	@echo "$(DEL_COLOR)Cleaning temporary files.$(NO_COLOR)"

fclean: clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out
	@echo "$(DEL_COLOR)Delete $(NAME) file.$(NO_COLOR)"

re: fclean all
