/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 03:47:11 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/09 21:44:24 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	here_doc_files(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->files_nb)
	{
		if (cmd->files[i].type == 2 && cmd->files->is_double)
		{
			i++;
			continue ;
		}
		cmd->files[i].fd = open(cmd->files[i].filename,
				O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 777);
		dup2(cmd->files[i].fd, STDOUT_FILENO);
		close (cmd->files[i].fd);
		i++;
	}
}

void	here_doc_utils(t_cmd *cmd, char *buffer, int i)
{
	int	fd;

	if (cmd->files_nb > 1)
		here_doc_files(cmd);
	free(cmd->files[i].filename);
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 777);
	cmd->files[i].filename = ft_strdup(".heredoc");
	write (fd, buffer, ft_strlen(buffer));
	close(fd);
}

void	ft_here_doc(t_cmd *cmd, int i)
{
	char	*tmp;
	char	*buffer;
	char	*no_nl;

	buffer = calloc(1, 1);
	while (TRUE)
	{
		write(1, "here_doc ➜ ", 13);
		tmp = get_next_line(0);
		no_nl = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		if (!ft_strcmp(no_nl, cmd->files[i].filename))
		{
			here_doc_utils(cmd, buffer, i);
			free(no_nl);
			free(tmp);
			break ;
		}
		buffer = ft_strjoin(buffer, tmp);
		free(no_nl);
		free(tmp);
	}
	free(buffer);
	buffer = NULL;
}
