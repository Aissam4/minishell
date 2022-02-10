/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_signe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:34:20 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 08:38:38 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *var, t_env *export)
{
	while (export)
	{
		if (!ft_memcmp(export->str, var, ft_strlen(var)))
			return (export->str);
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

static void	check_question_mark(t_cmd *cmd, int index)
{
	if (cmd->arguments[index][0] == DOLLAR_SIGNE
		&& cmd->arguments[index][1] == '?' && cmd->arguments[index][2] == '\0')
	{
		free(cmd->arguments[index]);
		if (g_tools.exit_status == 127)
			cmd->arguments[index] = ft_itoa(g_tools.exit_status);
		else
			cmd->arguments[index] = ft_itoa(WEXITSTATUS(g_tools.exit_status));
	}
}

static void	dollar_signe(t_cmd *cmd, t_env *export, int index, int count)
{
	char	*tmp_arg;
	char	**splited_args;
	char	**var;
	int		i;

	i = -1;
	check_question_mark(cmd, index);
	count = get_index(cmd->arguments[index], DOLLAR_SIGNE);
	if (count == -1)
		return ;
	tmp_arg = ft_substr(cmd->arguments[index], 0, count);
	splited_args = ft_split(&cmd->arguments[index][count], DOLLAR_SIGNE);
	var = (char **)malloc(sizeof(char *) * ft_strlen_2d(splited_args) + 1);
	if (!var)
		return (printf("failed allocation"), exit(1));
	while (splited_args[++i])
	{
		var[i] = get_var_value(get_var(splited_args[i], export));
		if (!var)
			return (free(tmp_arg), ft_free_env(var));
	}
	var[i] = NULL;
	free_dollar_sign_utils(index, cmd, tmp_arg, var);
	ft_free_env(splited_args);
}

void	parse_dollar_signe(t_cmd *cmd, t_env *export)
{
	int		index;

	while (cmd)
	{
		index = 0;
		while (cmd->arguments[++index])
			dollar_signe(cmd, export, index, 0);
		cmd = cmd->next;
	}
}
