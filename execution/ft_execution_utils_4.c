/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 08:12:37 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 08:24:22 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_cmd **cmd, t_pipe *pipe_, int savefd[2], t_env *export)
{
	char	*command;
	char	**env;

	env = lst_to_array(export);
	command = ft_check_excute(*cmd, env);
	if (!command)
	{
		printf("minishell: %s: command not found\n", (*cmd)->command);
		g_tools.exit_status = 127;
		ft_free_env(env);
		*cmd = (*cmd)->next;
		return (-1);
	}
	creat_process(*cmd, pipe_, savefd, export);
	free(command);
	g_tools.g_status = 1;
	ft_free_env(env);
	return (0);
}
