/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 07:50:07 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/07 02:42:04 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	red_in(t_cmd *cmd)
{
	cmd->files->fd = open(cmd->files->filename, O_RDONLY, 0644);
	if (cmd->files->fd < 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (-1);
	}
	dup2(cmd->files->fd, STDIN_FILENO);
	close (cmd->files->fd);
	return (0);
}

void	multi_redirection(t_cmd *cmd)
{
	while (cmd->files)
	{
		if (cmd->files->type == 5)
			ft_here_doc(cmd);
		else if (cmd->files->type == 2)
		{
			if (red_in(cmd) == -1)
				return ;
		}
		else if (cmd->files->type == 3)
		{
			cmd->files->fd = open(cmd->files->filename,
					O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
			dup2(cmd->files->fd, STDOUT_FILENO);
			close (cmd->files->fd);
		}
		else if (cmd->files->type == 4)
		{
			cmd->files->fd = open(cmd->files->filename,
					O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0644);
			dup2(cmd->files->fd, STDOUT_FILENO);
			close (cmd->files->fd);
		}
		cmd->files = cmd->files->next;
	}
}
