/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:50:55 by abarchil          #+#    #+#             */
/*   Updated: 2021/12/21 08:47:09 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	i;

	i = 0;
	str = (void *)malloc(size * count);
	if (!str)
		return (NULL);
	while (((char *)str) && i < count * size)
	{
		((char *)str)[i] = 0;
		i++;
	}
	return (str);
}
