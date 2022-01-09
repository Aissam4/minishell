/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:40:00 by abarchil          #+#    #+#             */
/*   Updated: 2021/12/23 19:40:34 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dest;
	char	*src;
	int		count;

	count = 0;
	src = (char *)s;
	dest = (char *)malloc(sizeof(const char) * n + 1);
	if (!dest)
		return (NULL);
	while (count < n)
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
