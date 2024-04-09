# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegros <clegros@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 16:52:09 by clegros           #+#    #+#              #
#    Updated: 2024/04/04 11:16:45 by clegros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRC		= minishell.c\
			lexer.c
OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
COMP	= $(CC) $(CFLAGS)
RM		= rm -f
DIR_INC	= -I02_pipex/
PIP_LIB	= 02_pipex/pipex.a


all:	$(NAME)

$(NAME): $(OBJ) $(PIP_LIB)
		$(COMP) $(OBJ) -o $(NAME) $(PIP_LIB) -lreadline

%.o: %.c
		$(CC) $(CFLAGS) $(DIR_INC) -c $< -o $@

$(PIP_LIB):
		@$(MAKE) -C 02_pipex

clean:
		$(RM) $(OBJ)
		@$(MAKE) -C 02_pipex clean

fclean: clean
		$(RM) $(NAME)
		@$(MAKE) -C 02_pipex fclean

re:		fclean all
