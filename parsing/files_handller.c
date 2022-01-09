/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-boua <fel-boua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 07:17:25 by fel-boua          #+#    #+#             */
/*   Updated: 2022/01/05 08:35:53 by fel-boua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handling_input(t_cmd *cmd)
{
	while (cmd->files)
	{
		if (cmd->files->type == 2)
		{
			dup2(cmd->files->fd, STDOUT_FILENO);
			close(cmd->files->fd);
		}
		else if (cmd->files->type == 3)
		{
			dup2(cmd->files->fd, STDOUT_FILENO);
			close(cmd->files->fd);
		}
		cmd->files = cmd->files->next;
	}
}
