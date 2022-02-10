/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:02:29 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 15:09:03 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_line(int fd)
{
	int		byte;
	int		i;
	char	line[1000000];
	char	buffer[1];

	ft_bzero(line, 1000000);
	i = 0;
	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, buffer, 1);
		line[i++] = buffer[0];
		if (buffer[0] == '\n')
			return (ft_strdup(line));
	}
	if (!line[0])
		return (NULL);
	return (ft_strdup(line));
}
