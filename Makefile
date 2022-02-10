# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 10:53:00 by atouhami          #+#    #+#              #
#    Updated: 2022/02/10 08:12:58 by abarchil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CSRC = parsing/main.c parsing/env.c parsing/parsing_utils.c parsing/wildcard.c \
	parsing/parsing.c parsing/lexing_functions.c parsing/lexing_utils_2.c \
	parsing/lexing_utils.c parsing/lexing.c parsing/libft_functions.c \
	src/ft_atoi.c src/ft_calloc.c src/ft_free_2d.c src/ft_lst_size.c src/ft_lstnew.c \
	src/ft_memcmp.c src/ft_memset.c src/ft_putstr_fd.c src/get_next_line.c \
	src/ft_bzero.c src/ft_del_node.c src/ft_isdigit.c src/ft_lstadd_back.c\
	src/ft_memchr.c  src/ft_memcpy.c  src/ft_putchar_fd.c \
	src/ft_split.c execution/cd_exec.c execution/check_command.c execution/echo_exec.c \
	execution/env_exec.c execution/exit_exec.c execution/export_exec.c execution/ft_execution.c \
	execution/ft_execution_utils.c execution/here_doc.c execution/lst_to_array.c \
	execution/multi_redirection.c execution/pwd_exec.c execution/unset_exec.c \
	parsing/parsing_dollar_signe.c src/ft_itoa.c execution/operations_utils.c \
	parsing/parsing_dollar_signe_utils.c src/ft_substr.c execution/ft_execution_utils_2.c \
	execution/ft_execution_utils_3.c execution/ft_execution_utils_4.c

RED = \033[0;31m

RESET = \033[0m

CYAN = \033[0;36m

YELLOW = \033[0;33m

OBJ = $(CSRC:.c=.o)
CFLAGS = -g -Wall -Werror -Wextra
CC = cc
NAME = minishell
HEADER = minishell.h

all : $(NAME)
	@echo "$(RED) \
			███╗   ███╗██╗███╗  ██╗██╗ ██████╗██╗  ██╗███████╗██╗     ██╗    \n\
			████╗ ████║██║████╗ ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
			██╔████╔██║██║██╔██╗██║██║╚█████╗ ███████║█████╗  ██║     ██║     \n\
			██║╚██╔╝██║██║██║╚████║██║ ╚═══██╗██╔══██║██╔══╝  ██║     ██║     \n\
			██║ ╚═╝ ██║██║██║ ╚███║██║██████╔╝██║  ██║███████╗███████╗███████╗\n\
			╚═╝     ╚═╝╚═╝╚═╝  ╚══╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \n $(RESET)"

%.o:%.c $(HEADER)
	@echo "$(CYAN)           		<----------- COMPILING $< -----------> $(RESET)"
	@$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L$(shell brew --prefix readline)/lib -lreadline  -o $(NAME)

clean :
	@echo "$(YELLOW)           		<----------- REMOVING OBJECT FILES ----------->$(RESET)"
	@rm -rf $(OBJ)
fclean : clean
	@echo "$(YELLOW)           		<----------- REMOVING MINISHELL ----------->$(RESET)"
	@rm -rf $(NAME)
re : fclean all

.PHONY : clean fclean re
