/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouhami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:58:47 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/11 18:58:49 by atouhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_wildcard(t_cmd *list)
{
	int	i;

	i = 0;
	if (list->wildcard_arguments)
	{
		while (list->wildcard_arguments[i])
			free(list->wildcard_arguments[i++]);
		free(list->wildcard_arguments);
	}
}

int	files_count(void)
{
	DIR				*dd;
	struct dirent	*dir;
	int				i;

	i = 1;
	dd = opendir(".");
	if (dd)
	{
		dir = readdir(dd);
		while (dir != NULL)
		{
			dir = readdir(dd);
			i++;
		}
	}
	closedir(dd);
	return (i - 2);
}

int	read_from_dir(DIR *dd, struct dirent *dir, char **args)
{
	int	i;

	i = 0;
	if (dd)
	{
		dir = readdir(dd);
		while (dir != NULL)
		{
			args[i] = ft_strdup(dir->d_name);
			if (!args[i])
				return (1);
			dir = readdir(dd);
			i++;
		}
		args[i] = NULL;
	}
	return (0);
}

char	**wildcard(char **wildcard)
{
	DIR				*dd;
	struct dirent	*dir;
	int				i;
	char			**args;

	args = NULL;
	i = files_count();
	if (i > 1 && !wildcard)
	{
		dd = opendir(".");
		dir = readdir(dd);
		dir = readdir(dd);
		args = malloc(sizeof(char *) * i + 1);
		if (!args)
			return (printf("failed allocation"), exit(1), NULL);
		if (read_from_dir(dd, dir, args))
			return (NULL);
		closedir(dd);
	}
	if (!wildcard)
		return (args);
	return (wildcard);
}
