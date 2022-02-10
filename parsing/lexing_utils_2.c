/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:06:29 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/14 13:54:32 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_list(t_tokens *list, char *str, t_env *env, int was_in_while)
{
	int	i;

	i = 0;
	define_type(str, i, list);
	while (str[i] && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && str[i] != '*' && str[i] != '&' && str[i] != ' ')
	{
		was_in_while = 1;
		if (str[i] == '\'')
			i = skip_quotes(str, i, '\'');
		if (str[i] == '\"')
			i = skip_quotes(str, i, '\"');
		if (str[i] == '\"' || str[i] == '\'')
			break ;
		i++;
		if (str[i] == '\"' || str[i] == '\'')
			break ;
	}
	if ((str[i] == '|' || str[i] == '>' || str[i] == '&'
			|| str[i] == '<' || str[i] == '*') && was_in_while)
	{
		i--;
		list->credit += 1;
	}
	fill_infos(str, i, list, env);
}

void	lexer_assign(t_tokens *head, t_tokens *next, char *str, t_env *env)
{
	int	i;

	i = 0;
	if (str && str[0])
	{
		head->credit = 0;
		fill_list(head, str, env, 0);
		i = head->lenght + 1;
		head->lenght += head->credit;
	}
	while (i < ft_strlen(str))
	{
		next->lenght = 0;
		while (str[i] == ' ')
			i++;
		if (str[i])
		{
			next->credit = 0;
			fill_list(next, str + i, env, 0);
			i += next->lenght + 1;
			next->lenght += next->credit;
			list_create(next);
			next = next->next;
		}
	}
}

void	free_all(t_tokens *head)
{
	t_tokens	*next;
	t_tokens	*tmp;

	next = head->next;
	free(head);
	while (next)
	{
		tmp = next;
		next = next->next;
		free(tmp);
	}
}

int	check_types(t_tokens *list)
{
	while (list->next)
	{
		if (list && list->type == PIPE)
			if (list->next && list->next->type == PIPE)
				if ((list->next->next && list->next->next->type == PIPE)
					|| list->next->str[-1] != '|')
					return (printf("parse error near '|'\n"), 1);
		if (list && list->type == AND)
			if (list->next && list->next->type == AND)
				if ((list->next->next && list->next->next->type == AND)
					|| list->next->str[-1] != '&')
					return (printf("parse error near '&'\n"), 1);
		if (list && list->type == REDIRECTION)
			if (list->next && list->next->type == REDIRECTION)
				if ((list->next->next && list->next->next->type == REDIRECTION)
					|| (list->next->str[-1] != '>'
						&& list->next->str[-1] != '<'))
					return (printf("parse error near redirection\n"), 1);
		if (list && list->next && list->type == REDIRECTION
			&& list->next->type == REDIRECTION)
			if (list->redirection_type != list->next->redirection_type)
				return (printf("parse error near redirection\n"), 1);
		list = list->next;
	}
	return (0);
}

int	lexer(char *str, t_env *env)
{
	t_tokens	*head;
	t_tokens	*next;

	head = list_create(NULL);
	next = list_create(head);
	if (!(*str))
		return (1);
	if (!head || !next)
		return (printf("Error during allocation"), 0);
	head->lenght = 0;
	lexer_assign(head, next, str, env);
	if (!check_types(head) && !check_types_two(head))
	{
		while (next->next)
			next = next->next;
		if (((head->type != COMMAND && head->type <= REDIRECTION)
				|| next->previous->type > WILDCARD))
			printf("Error : Syntax Error !\n");
		else
			parse_to_command(head, NULL, NULL);
	}
	free_all(head);
	return (1);
}
