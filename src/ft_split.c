/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:55:52 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 15:19:54 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_2(char const *s1, char const *s2)
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
	return (s);
}

static void	*ft_memzero(int size)
{
	char	*dest;
	int		count;

	count = 0;
	dest = (char *)malloc(sizeof(char) * size);
	if (dest)
	{
		while (size != 0)
		{
			dest[count++] = 0;
			size--;
		}
		return (dest);
	}
	else
		return (printf("failed allocation"), exit(1), NULL);
}

static int	word_length(char const *s, char c)
{
	int	len;

	len = 0;
	if (*s != c && *s != 0)
	{
		len++;
		s++;
	}
	while (*s != 0)
	{
		if (*s != c)
			len++;
		s++;
	}
	return (len + 1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	count;
	unsigned int	j;
	char			**splited;

	if (s == NULL)
		return (NULL);
	splited = (char **)malloc(sizeof(char *) * word_length(s, c));
	if (!splited)
		return (printf("failed allocation"), exit(1), NULL);
	j = 0;
	while (*s != 0)
	{
		count = 0;
		while (s[count] != c && s[count] != 0)
			count++;
		if (count)
		{
			splited[j++] = ft_memcpy(ft_memzero(count + 1), s, count);
			s = &s[count];
		}
		else
			s++;
	}
	splited[j] = NULL;
	return (splited);
}
