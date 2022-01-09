/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:16:48 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/07 21:31:01 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_builting(char *command)
{
	if (!ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "ECHO")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "PWD")
		|| !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "EXIT")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "CD")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "EXPORT")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "UNSET")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "ENV"))
		return (0);
	else
		return (-1);
}

int	check_command(t_cmd *cmd, t_export *export)
{
	if (cmd->command)
	{
		if (!ft_strcmp(cmd->command, "echo")
			|| !ft_strcmp(cmd->command, "ECHO"))
			return (ft_echo(cmd));
		else if (!ft_strcmp(cmd->command, "pwd")
			|| !ft_strcmp(cmd->command, "PWD"))
			return (ft_pwd(cmd, export));
		else if (!ft_strcmp(cmd->command, "exit")
			|| !ft_strcmp(cmd->command, "EXIT"))
			return (ft_exit(cmd));
		else if (!ft_strcmp(cmd->command, "cd")
			|| !ft_strcmp(cmd->command, "CD"))
			return (ft_cd(cmd, export));
		else if (!ft_strcmp(cmd->command, "export")
			|| !ft_strcmp(cmd->command, "EXPORT"))
			return (ft_export(cmd, export));
		else if (!ft_strcmp(cmd->command, "unset")
			|| !ft_strcmp(cmd->command, "UNSET"))
			return (ft_unset(cmd, export));
		else if (!ft_strcmp(cmd->command, "env")
			|| !ft_strcmp(cmd->command, "ENV"))
			return (ft_env(export));
	}
	return (-1);
}
