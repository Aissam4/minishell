/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:51:59 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 15:09:52 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*str;
	int				count;

	str = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		if (*str == (unsigned char)c)
			return (str);
		count++;
		str++;
	}
	return (0);
}
