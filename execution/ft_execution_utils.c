/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 03:00:25 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/07 03:37:28 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			tmp = ft_strjoin(splited_path[i], "/");
	else
		tmp = ft_strdup(splited_path[i]);
	finall_path = ft_strjoin(tmp, cmd->command);
	if (access(finall_path, X_OK | F_OK) == 0)
	{
		ft_free_2d(splited_path);
		return (finall_path);
	}
	free(finall_path);
	finall_path = NULL;
	i++;
	return (NULL);
}

char	*ft_check_excute(t_cmd *cmd, char **env)
{
	int		i;
	char	**splited_path;
	char	*finall_path;

	if (ft_strchr(cmd->command, '/'))
		return (cmd->command);
	splited_path = ft_split(ft_check_path(env), ':');
	i = 0;
	while (splited_path[i])
	{
		finall_path = splithed_path(cmd, i, finall_path, splited_path);
		if (finall_path)
			return (finall_path);
			i++;
	}
	free(splited_path);
	splited_path = NULL;
	return (NULL);
}
