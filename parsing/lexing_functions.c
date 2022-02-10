/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:06:19 by atouhami          #+#    #+#             */
/*   Updated: 2022/02/09 21:48:21 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *string, int searchedChar)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)searchedChar)
			return (string + i);
		i++;
	}
	if (string[i] == searchedChar)
	{
		return (string + i);
	}
	return (NULL);
}

char	*ft_substr(char const *s, int start, int len)
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
	return (s2);
}

void	handler(int sig)
{
	(void)sig;
	if (g_tools.g_status == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	starts_with(char *str, char *tofind)
{
	int	i;

	i = 0;
	if (str)
	{
		while (*str == ' ')
			str++;
		while (tofind[i])
		{
			if (tofind[i] != str[i])
				return (0);
			i++;
		}
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
	}
	return (1);
}

int	verifiy_quotes(char *line, char c, char ignore)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == ignore && line[i - 1] != '\\')
			i = skip_quotes(line, i, ignore);
		if (line[i] == c && line[i - 1] != '\\')
			counter++;
		i++;
	}
	if (counter % 2 == 0)
		return (1);
	return (0);
}
