# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 22:07:03 by abarchil          #+#    #+#              #
#    Updated: 2022/01/08 01:42:26 by abarchil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILE = main.c src/ft_strjoin.c src/ft_memcmp.c src/ft_split.c execution/export_exec.c \
	src/ft_strchr.c src/ft_strcmp.c parsing/minishell_init.c execution/pwd_exec.c \
	src/ft_calloc.c src/ft_del_node.c src/ft_isalpha.c src/ft_memcpy.c src/ft_lstnew.c \
	src/ft_memmove.c src/ft_memset.c src/ft_putstr_fd.c src/ft_putchar_fd.c src/ft_remchar.c \
	src/ft_strdup.c src/ft_strlen.c src/ft_strtrim.c src/ft_substr.c src/get_next_line.c \
	src/ft_bzero.c src/ft_lstadd_back.c parsing/lexing.c parsing/parsing.c src/ft_strndup.c \
	parsing/parsing_dollar_signe.c src/ft_free_2d.c execution/ft_execution.c src/ft_lst_size.c \
	execution/echo_exec.c src/ft_isdigit.c execution/exit_exec.c src/ft_atoi.c execution/cd_exec.c \
	execution/unset_exec.c execution/env_exec.c execution/check_command.c parsing/files_handller.c \
	execution/signales.c parsing/lst_to_array.c execution/here_doc.c src/ft_itoa.c execution/multi_redirection.c \
	execution/ft_execution_utils.c parsing/lexing_utils.c

OBJ_FILE = $(SRC_FILE:.c=.o)

NAME = minishell

CC = gcc

RED = \033[0;31m

RESET = \033[0m

CYAN = \033[0;36m

YELLOW = \033[0;33m

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)
	@echo "$(RED) \
			███╗   ███╗██╗███╗  ██╗██╗ ██████╗██╗  ██╗███████╗██╗     ██╗    \n\
			████╗ ████║██║████╗ ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
			██╔████╔██║██║██╔██╗██║██║╚█████╗ ███████║█████╗  ██║     ██║     \n\
			██║╚██╔╝██║██║██║╚████║██║ ╚═══██╗██╔══██║██╔══╝  ██║     ██║     \n\
			██║ ╚═╝ ██║██║██║ ╚███║██║██████╔╝██║  ██║███████╗███████╗███████╗\n\
			╚═╝     ╚═╝╚═╝╚═╝  ╚══╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \n $(RESET)"
#	@echo "           		MADE WITH 💜 BY : abarchil & fel-boua $(RED)"
%.o:%.c
	@echo "$(CYAN)           		<----------- COMPILING $< -----------> $(RESET)"
	@$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ_FILE)
	@$(CC) $(CFLAGS) $(OBJ_FILE) -L$(shell brew --prefix readline)/lib   -lreadline  -o $(NAME)

clean :
	@echo "$(YELLOW)           		<----------- REMOVING OBJECT FILES ----------->$(RESET)"
	@rm -rf $(OBJ_FILE)
fclean : clean
	@echo "$(YELLOW)           		<----------- REMOVING MINISHELL ----------->$(RESET)"
	@rm -rf $(NAME)
re : fclean all

.PHONY : clean fclean re 