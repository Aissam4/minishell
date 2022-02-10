/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:25:59 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/17 10:48:57 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arguments(t_cmd *list)
{
	int	i;

	i = 0;
	if (list -> args)
	{
		while (list->args && list->args[i])
			free(list->args[i++]);
		free(list->args);
	}
	i = 0;
	if (list -> arguments)
	{
		while (list->arguments && list->arguments[i])
			free(list->arguments[i++]);
		free(list->arguments);
	}
}

char	**merge_args(char **arguments, char **wildcard)
{
	int		i;
	int		j;
	char	**args;

	j = 0;
	i = 0;
	if (arguments)
		while (arguments[i])
			i++;
	if (wildcard)
		while (wildcard[j++])
			i++;
	args = malloc(sizeof(char *) * i + 1);
	if (!args)
		return (printf("failed allocation"), exit(1), NULL);
	args[i] = NULL;
	i = -1;
	if (arguments)
		while (arguments[++i])
			args[i] = ft_strdup(arguments[i]);
	j = 0;
	if (wildcard)
		while (wildcard[j])
			args[i++] = ft_strdup(wildcard[j++]);
	return (args);
}

void	fill_cmd_name_wild(t_tokens *list, t_cmd *cmd)
{
	if (list->type == COMMAND)
	{
		cmd->command = get_arg(list);
		cmd->args[0] = ft_strdup(cmd->command);
	}
	if (list->type == WILDCARD)
		cmd->wildcard_arguments = wildcard(cmd->wildcard_arguments);
}

char	*get_arg(t_tokens *list)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	if (list->str[0] == '\"' || list->str[0] != '\'')
	{
		while (i < list->lenght)
		{
			if (list->str[i] == '$')
				list->str[i] = DOLLAR_SIGNE;
			i++;
		}
	}
	if (list->str[0] == '\"' || list->str[0] == '\'')
	{
		start++;
		list->lenght -= 1;
	}
	return (ft_substr(list->str, start, list->lenght));
}

char	*ft_strtrim(char *s1, char *set)
{
	unsigned int	count;
	unsigned int	str_count;
	unsigned int	s1_size;
	char			*str;

	count = 0;
	str_count = 0;
	s1_size = ft_strlen(s1) - 1;
	while (s1[count] && ft_strchr(set, s1[count]) != 0)
		count++;
	if (s1[count] == '\0')
		return (free(s1), ft_strdup(""));
	while (s1_size > count && ft_strchr(set, s1[s1_size]) != 0)
		s1_size--;
	str = (char *)malloc(sizeof(char) * (s1_size - count) + 1);
	if (!str)
		return (printf("failed allocation"), exit(1), NULL);
	while (count <= s1_size)
		str[str_count++] = s1[count++];
	str[str_count] = '\0';
	free(s1);
	return (str);
}
