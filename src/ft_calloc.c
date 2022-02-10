/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:50:55 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 15:09:52 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(int count, int size)
{
	void	*str;
	int		i;

	i = 0;
	str = (void *)malloc(size * count);
	if (!str)
		return (printf("failed allocation"), exit(1), NULL);
	while (((char *)str) && i < count * size)
	{
		((char *)str)[i] = 0;
		i++;
	}
	return (str);
}
