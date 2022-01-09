/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-boua <fel-boua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:36:43 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/08 02:57:37 by fel-boua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
