/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:40:19 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 07:40:33 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	and_or_operation(t_cmd *cmd, t_env *export, t_pipe *pipe_, char **env)
{
	char	*command;

	pipe_->pid = fork();
	if (pipe_->pid == 0)
	{
		command = ft_check_excute(cmd, env);
		if (!check_if_builting(cmd->command) && cmd->next)
			exit(check_command(cmd, export));
		check_command_error(cmd, export, command, env);
	}
	else
		wait(&g_tools.exit_status);
}
