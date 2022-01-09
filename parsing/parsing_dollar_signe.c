/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_signe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 07:16:06 by fel-boua          #+#    #+#             */
/*   Updated: 2022/01/08 01:37:30 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var(char *var, t_export *export)
{
	while (export)
	{
		if (!ft_memcmp(export->variable, var, ft_strlen(var)))
			return (export->variable);
		export = export->next;
	}
	return (NULL);
}

char	*get_var_value(char *variable)
{
	int	index;

	index = 0;
	if (!variable)
		return (NULL);
	while (variable[index] && variable[index] != '=')
		index++;
	if (!variable[index])
		return (NULL);
	index++;
	return (ft_substr(variable, index, ft_strlen(variable) - index));
}

static void	check_question_mark(char *arg)
{
	free(arg);
	arg = ft_itoa(g_tools.exit_status);
}

static void	dollar_signe(t_cmd *cmd, t_export *export, int index, int count)
{
	char	*var;
	char	*tmp_arg;

	if (ft_strchr(cmd->args[index], DOLLAR_SIGNE))
	{
		if (cmd->args[index][0] == DOLLAR_SIGNE && cmd->args[index][1] == '?')
			check_question_mark(cmd->args[index]);
		while (cmd->args[index][count]
			&& cmd->args[index][count] != DOLLAR_SIGNE)
			count++;
		if (!cmd->args[index][count])
			return ;
		tmp_arg = ft_substr(cmd->args[index], 0, count);
		var = remchar(get_var_value(get_var
					(&cmd->args[index][count + 1], export)), '\"');
		if (!var)
		{
			cmd->args[index] = NULL;
			return (free(tmp_arg));
		}
		free(cmd->args[index]);
		cmd->args[index] = ft_strjoin(tmp_arg, var);
		free(tmp_arg);
		free(var);
	}
}

void	parse_dollar_signe(t_cmd *cmd, t_export *export)
{
	int		index;
	int		count;

	count = 0;
	while (cmd)
	{
		index = 0;
		while (cmd->args[++index])
			dollar_signe(cmd, export, index, 0);
		cmd = cmd->next;
	}
}
