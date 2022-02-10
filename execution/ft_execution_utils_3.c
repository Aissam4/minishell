/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 04:05:22 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 08:24:03 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	finish_execution(char **env)
{
	int	r;

	r = 0;
	unlink(".heredoc");
	ft_free_env(env);
	while (r != -1)
		r = wait(&g_tools.exit_status);
	signal_exit_code();
}

void	child_process(t_cmd *cmd, t_pipe *pipe_, char **env, char *command)
{
	multi_redirection(cmd, 0);
	close(pipe_->pipefd[R]);
	execve(command, cmd->arguments, env);
}

void	creat_process(t_cmd *cmd, t_pipe *pipe_, int savefd[2], t_env *export)
{
	char	**env;
	char	*command;

	env = lst_to_array(export);
	command = ft_check_excute(cmd, env);
	g_tools.g_status = 1;
	pipe_->pid = fork();
	if (pipe_->pid == -1)
		ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
	if (pipe_->pid == 0)
		child_process(cmd, pipe_, env, command);
	else
		parent_process(cmd, pipe_, savefd, command);
	ft_free_env(env);
}

int	operations(t_cmd *cmd, t_pipe *pipe_, int savefd[2], t_env *export)
{
	char	**env;

	env = lst_to_array(export);
	dup2(savefd[STDOUT_FILENO], STDOUT_FILENO);
	and_or_operation(cmd, export, pipe_, env);
	ft_free_env(env);
	return (0);
}

int	operation_etiration(t_cmd *cmd, t_pipe *pipe_, int savefd[2], t_env *export)
{
	operations(cmd, pipe_, savefd, export);
	if ((cmd->next_operation == OP_AND && g_tools.exit_status != 0)
		|| (cmd->next_operation == OP_OR && g_tools.exit_status == 0))
		return (-1);
	else
		return (0);
}
