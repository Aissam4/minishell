/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:36:43 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/16 17:00:45 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_index(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

void	ft_free_2d(char **av)
{
	int		index;

	index = 0;
	while (av && av[++index])
	{
		free(av[index]);
		av[index] = NULL;
	}
	if (av)
		free(av);
}

void	ft_free_env(char **av)
{
	int		index;

	index = -1;
	while (av && av[++index])
	{
		free(av[index]);
		av[index] = NULL;
	}
	if (av)
		free(av);
}
