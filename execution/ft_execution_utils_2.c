/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:06:33 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 08:35:12 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_fd(int savefd[2])
{
	dup2(savefd[STDIN_FILENO], STDIN_FILENO);
	close(savefd[STDIN_FILENO]);
	dup2(savefd[STDOUT_FILENO], STDOUT_FILENO);
	close(savefd[STDOUT_FILENO]);
}

void	signal_exit_code(void)
{
	if (WIFEXITED(g_tools.exit_status))
		WEXITSTATUS(g_tools.exit_status);
	if (WIFSIGNALED(g_tools.exit_status))
		g_tools.exit_status = (WTERMSIG(g_tools.exit_status) + 128) * 256;
}

void	parent_process(t_cmd *cmd, t_pipe *pipe_, int savefd[2], char *command)
{
	(void)command;
	close(pipe_->pipefd[W]);
	if (!cmd->next)
		dup2(savefd[STDIN_FILENO], STDIN_FILENO);
	else
		postexec(pipe_->pipefd);
	free(command);
	command = NULL;
}

int	creat_pipe(t_cmd *cmd, t_pipe *pipe_, char **env, int savefd[2])
{
	if (cmd->next && pipe(pipe_->pipefd) == -1)
	{
		ft_free_env(env);
		perror("pipe");
		return (-1);
	}
	if (!cmd->next)
		dup2(savefd[STDOUT_FILENO], STDOUT_FILENO);
	else
		preexec(pipe_->pipefd);
	return (0);
}

int	check_builtins(t_cmd *cmd, char **env, t_env *export, t_pipe *pipe_)
{
	if (!cmd->command[0])
	{
		ft_free_env(env);
		return (-1);
	}
	if (!check_if_builting(cmd->command) && !cmd->next && cmd->files_nb)
	{
		builting_child(pipe_, cmd, export);
		ft_free_env(env);
		return (-1);
	}
	else if (!check_if_builting(cmd->command) && !cmd->next)
	{
		check_command(cmd, export);
		ft_free_env(env);
		return (-1);
	}
	return (0);
}
