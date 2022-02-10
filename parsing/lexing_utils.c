/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:06:25 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/13 12:13:31 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_errors(char *line)
{
	if (!verifiy_quotes(line, '\'', '\"') || !verifiy_quotes(line, '\"', '\''))
		return (printf("Error : Unterminated quotes\n"), 1);
	return (0);
}

t_tokens	*list_create(t_tokens *previous_last)
{
	t_tokens	*list;

	list = malloc(sizeof(t_tokens));
	if (!list)
		return (printf("failed allocation"), exit(1), NULL);
	list->next = NULL;
	if (previous_last)
		previous_last->next = list;
	list->previous = previous_last;
	return (list);
}

int	skip_quotes(char *str, int i, char c)
{
	int	j;

	j = 0;
	while (j != 2 && str[i])
	{
		if (str[i] == c && str[i - 1] != '\\')
			j++;
		i++;
	}
	i--;
	return (i);
}

void	define_type(char *str, int i, t_tokens *list)
{
	list->redirection_type = 0;
	list->type = STRING;
	if ((list->previous == NULL || list->previous->type == PIPE
			|| list->previous->type == AND))
		list->type = COMMAND;
	else if (list->previous->type == REDIRECTION)
		list->type = FILE;
	if (str[i] == '|')
		list->type = PIPE;
	if (str[i] == '&')
		list->type = AND;
	if (str[i] == '*')
		list->type = WILDCARD;
	if (str[i] == '>' || str[i] == '<')
	{
		list->type = REDIRECTION;
		if (str[i] == '>')
			list->redirection_type = 1;
		else
			list->redirection_type = 2;
	}
}

void	fill_infos(char *str, int i, t_tokens *list, t_env *env)
{
	int		start;

	list->env = env;
	list->str = str;
	list->lenght = i;
	start = 0;
	if (list->type == FILE)
	{
		if (str[start] == '\'' || str[start] == '\"')
		{
			start++;
			i--;
		}
		list->filename = ft_substr(str, start, i);
	}
}
