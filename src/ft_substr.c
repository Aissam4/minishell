/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:06:33 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/09 21:48:51 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_2(char const *s, int start, int len)
{
	char	*s2;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (printf("failed allocation"), exit(1), NULL);
	ft_memmove(s2, &s[start], len);
	s2[len] = '\0';
	free((char *)s);
	return (s2);
}
