/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 03:00:25 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/09 23:02:51 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_path(char **env)
{
	char	*path_line;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			path_line = env[i];
			return (path_line + 5);
		}
		i++;
	}
	return (NULL);
}

static char	*splithed_path(t_cmd *cmd, int i,
		char *finall_path, char **splited_path)
{
	char	*tmp;

	if (splited_path[i][ft_strlen(splited_path[i])] != '/')
			tmp = ft_strjoin_2(splited_path[i], "/");
	else
		tmp = ft_strdup(splited_path[i]);
	finall_path = ft_strjoin_2(tmp, cmd->command);
	if (access(finall_path, X_OK | F_OK) == 0)
	{
		free(tmp);
		ft_free_env(splited_path);
		return (finall_path);
	}
	free(finall_path);
	finall_path = NULL;
	free(tmp);
	i++;
	return (NULL);
}

char	*ft_check_excute(t_cmd *cmd, char **env)
{
	int		i;
	char	**splited_path;
	char	*finall_path;

	if (ft_strchr(cmd->command, '/'))
	{
		if (access(cmd->command, X_OK | F_OK) == 0)
			return (ft_strdup(cmd->command));
		else
			return (NULL);
	}
	splited_path = ft_split(ft_check_path(env), ':');
	if (!splited_path)
		return (NULL);
	i = 0;
	while (splited_path[i])
	{
		finall_path = splithed_path(cmd, i, finall_path, splited_path);
		if (finall_path)
			return (finall_path);
		i++;
	}
	ft_free_env(splited_path);
	splited_path = NULL;
	return (NULL);
}

void	check_command_error(t_cmd *cmd, t_env *export,
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
		execve(command, cmd->arguments, env);
	else if (!command)
	{
		printf("minishell: %s: command not found\n", cmd->command);
		free(command);
		command = NULL;
		g_tools.exit_status = 127;
		exit(127);
	}
}

void	builting_child(t_pipe *pipe_, t_cmd *cmd, t_env *export)
{
	pipe_->pid = fork();
	if (pipe_->pid == 0)
	{
		multi_redirection(cmd, 0);
		check_command(cmd, export);
		exit(0);
	}
	else
		wait(&g_tools.exit_status);
	return ;
}
