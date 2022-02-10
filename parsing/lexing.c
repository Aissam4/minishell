/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:06:15 by atouhami          #+#    #+#             */
/*   Updated: 2022/02/10 08:46:41 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_types_two(t_tokens *list)
{
	while (list->next)
	{
		if (list && list->type >= 2)
		{
			if ((list->next && list->next->type >= 2)
				&& (list->next && list->next->type != list->type))
				return (printf("parse error\n"), 1);
		}
		if (list && list->type == AND)
			if ((list->next && list->next->type != AND)
				&& (list->previous && list->previous->type != AND))
				return (printf("parse error near '&'\n"), 1);
		if (list->str[ft_strlen(list->str) - 1] == ';'
			&& list->str[ft_strlen(list->str) - 2] == ';')
			return (printf("parse error near ';;'\n"), 1);
		list = list->next;
	}
	return (0);
}

void	define_next_operation(t_tokens *list, t_cmd *cmd)
{
	cmd->next_operation = OP_NONE;
	if (cmd->previous && list->previous && list->previous->previous
		&& list->previous->type == PIPE
		&& list->previous->previous->type == PIPE)
		cmd->previous->next_operation = OP_OR;
	else if (cmd->previous && list->previous && list->previous->type == PIPE)
		cmd->previous->next_operation = OP_PIPE;
	else if (cmd->previous && list->previous && list->previous->type == AND)
		cmd->previous->next_operation = OP_AND;
}

void	set_to_value(int *i, int *f_nb)
{
	*i = 1;
	*f_nb = 0;
}

void	take_command(char *str, t_env *env)
{
	while (*str == ' ')
		str++;
	if (verify_errors(str) || !str[0] || !lexer(str, env))
		return ;
}

int	count_elements(t_tokens *list, int element)
{
	int	i;

	i = 0;
	while (list->type != PIPE && list->type != AND && list->next)
	{
		if (list->type == element)
			i++;
		list = list-> next;
	}
	return (i);
}
