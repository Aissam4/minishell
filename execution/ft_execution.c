/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:44:57 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/08 02:04:55 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(t_cmd *cmd, int cmd_count,
			t_pipe *pipe_, t_export *export)
{
	char	*command;
	char	**env;

	env = lst_to_array(export);
	while (cmd_count - 1)
	{
		execute_command(pipe_, cmd, export);
		cmd_count--;
		cmd = cmd->next;
	}
	multi_redirection(cmd);
	command = ft_check_excute(cmd, env);
	check_command_error(cmd, export, command, env);
	ft_free_2d(env);
}

void	check_command_error(t_cmd *cmd, t_export *export,
	char *command, char **env)
{
	if (!check_if_builting(cmd->command) && cmd->next)
	{
		check_command(cmd, export);
		exit(0);
	}
	if (!check_if_builting(cmd->command))
		check_command(cmd, export);
	else if (command)
		execve(command, cmd->args, env);
	else if (!command)
	{
		printf("minishell: %s: command not found\n", cmd->command);
		free(command);
		exit(127);
	}
	free(command);
}

void	execute_command(t_pipe *pipe_, t_cmd *cmd, t_export *export)
{
	char	*command;
	char	**env;

	env = lst_to_array(export);
	pipe(pipe_->pipefd);
	pipe_->pid = fork();
	if (pipe_->pid == 0)
	{
		multi_redirection(cmd);
		dup2(pipe_->pipefd[W], STDOUT_FILENO);
		close(pipe_->pipefd[W]);
		close(pipe_->pipefd[R]);
		command = ft_check_excute(cmd, env);
		if (!check_if_builting(cmd->command) && cmd->next)
			exit(check_command(cmd, export));
		check_command_error(cmd, export, command, env);
	}
	else
	{
		close(pipe_->pipefd[W]);
		dup2(pipe_->pipefd[R], STDIN_FILENO);
		close(pipe_->pipefd[R]);
		wait(&g_tools.exit_status);
	}
}

void	ft_execution(t_pipe *pipe_, t_cmd *cmd, t_export *export)
{
	int		cmd_count;
	char	**env;

	env = lst_to_array(export);
	cmd_count = ft_lstsize(cmd);
	if (!cmd->command)
		return ;
	if (!check_if_builting(cmd->command) && !cmd->next)
	{
		check_command(cmd, export);
		return ;
	}
	if (pipe(pipe_->pipefd) == -1)
		return (perror("pipe"));
	pipe_->pid = fork();
	if (pipe_->pid == -1)
		return (perror("fork"));
	if (pipe_->pid == 0)
		child_process(cmd, cmd_count, pipe_, export);
	else
	{
		close(pipe_->pipefd[R]);
		close(pipe_->pipefd[W]);
		wait(&g_tools.exit_status);
	}
}
