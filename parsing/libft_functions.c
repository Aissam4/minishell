/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:06:34 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/16 17:29:20 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, int n)
{
	int		i;
	char	*psrc;
	char	*pdest;

	psrc = (char *)src;
	pdest = (char *)dest;
	if (dest > src)
	{
		i = n - 1;
		while (n--)
		{
			pdest[i] = psrc[i];
			i--;
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (n--)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strdup(const char *source)
{
	int		i;
	char	*dst;

	i = 0;
	if (!source)
		return (NULL);
	while (source[i])
		i++;
	dst = malloc(i * sizeof(char) + 1);
	if (dst == NULL)
		return (printf("failed allocation"), exit(1), NULL);
	i = 0;
	while (source[i])
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1)
		return (-1);
	i = 0;
	while (s1[i] == s2[i])
	{
		i++;
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s;
	int			s1len;
	int			s2len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	s = malloc((s1len + s2len) * sizeof(char));
	if (s == NULL)
		return (printf("failed allocation"), exit(1), NULL);
	ft_memmove(s, s1, s1len);
	ft_memmove(&s[s1len], s2, s2len);
	s[s1len + s2len] = '\0';
	free((void *)s1);
	return (s);
}
