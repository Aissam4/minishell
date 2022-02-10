/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:44:57 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 08:23:37 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preexec(int pipe[2])
{
	dup2(pipe[W], STDOUT_FILENO);
	close(pipe[W]);
}

void	postexec(int pipe[2])
{
	dup2(pipe[R], STDIN_FILENO);
	close (pipe[R]);
}

void	ft_execution(t_pipe *pipe_, t_cmd *cmd, t_env *export)
{
	char	**env;
	int		savefd[2];

	env = lst_to_array(export);
	if (check_builtins(cmd, env, export, pipe_) == -1)
		return ;
	savefd[STDIN_FILENO] = dup(STDIN_FILENO);
	savefd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while (cmd)
	{
		if (creat_pipe(cmd, pipe_, env, savefd) == -1)
			return ;
		while (cmd->next_operation == OP_AND || cmd->next_operation == OP_OR)
		{
			if (operation_etiration(cmd, pipe_, savefd, export) == -1)
				return (ft_free_env(env));
			cmd = cmd->next;
		}
		if (execute_cmd(&cmd, pipe_, savefd, export) == -1)
			continue ;
		cmd = cmd->next;
	}
	reset_fd(savefd);
	finish_execution(env);
}
