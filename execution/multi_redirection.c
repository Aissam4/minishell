/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 07:50:07 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/09 22:57:21 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_in(t_cmd *cmd, int i)
{
	cmd->files[i].fd = open(cmd->files[i].filename, O_RDONLY, 777);
	if (cmd->files[i].fd < 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (-1);
	}
	dup2(cmd->files[i].fd, STDIN_FILENO);
	close (cmd->files[i].fd);
	if (cmd->files[i].type == 2 && cmd->files->is_double)
		unlink(".heredoc");
	return (0);
}

void	red_out(t_cmd *cmd, int i)
{
	cmd->files[i].fd = open(cmd->files[i].filename,
			O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	if (cmd->files[i].fd < 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		g_tools.exit_status = 1;
		exit(1);
	}
	dup2(cmd->files[i].fd, STDOUT_FILENO);
	close(cmd->files[i].fd);
}

void	multi_redirection(t_cmd *cmd, int i)
{
	while (i < cmd->files_nb)
	{
		if (cmd->files[i].type == 2 && cmd->files->is_double)
		{
			ft_here_doc(cmd, i);
			if (red_in(cmd, i) == -1)
				return ;
		}
		else if (cmd->files[i].type == 2 && !cmd->files->is_double)
		{
			if (red_in(cmd, i) == -1)
				return ;
		}
		else if (cmd->files[i].type == 1 && !cmd->files->is_double)
			red_out(cmd, i);
		else if (cmd->files[i].type == 1 && cmd->files->is_double)
		{
			cmd->files[i].fd = open(cmd->files[i].filename,
					O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0644);
			dup2(cmd->files[i].fd, STDOUT_FILENO);
			close (cmd->files[i].fd);
		}
		i++;
	}
}
