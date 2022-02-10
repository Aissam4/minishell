/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 08:17:45 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 06:47:59 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_pwd(t_env *export)
{
	char		*tmp2;
	t_env		*tmp;

	tmp = export;
	tmp2 = NULL;
	while (tmp)
	{
		if (!ft_memcmp(tmp->str, "OLDPWD", 6))
		{
			free(tmp->str);
			tmp2 = getcwd(tmp2, sizeof(tmp2));
			tmp->str = ft_strjoin_2("OLDPWD=", tmp2);
			free(tmp2);
			tmp2 = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

char	*ft_search_in_list(t_env *export, char *name)
{
	t_env	*temp;

	temp = export;
	if (temp == NULL)
		return (NULL);
	while (temp)
	{
		if (!ft_memcmp(temp->str, name, ft_strlen(name)))
			return (temp->str);
		temp = temp->next;
	}
	temp = NULL;
	return (NULL);
}

void	ft_replace_directory(t_env *export)
{
	char	*buff;
	char	*new_dir;

	buff = NULL;
	new_dir = getcwd(buff, sizeof(buff));
	while (export)
	{
		if (!ft_memcmp(export->str, "PWD", 3))
			break ;
		export = export->next;
	}
	free(export->str);
	export->str = ft_strjoin_2("PWD=", new_dir);
	free(new_dir);
	new_dir = NULL;
}

int	change_directory(char *dir, t_env *export)
{
	replace_pwd(export);
	if (chdir(dir) == -1)
		return (perror("cd"), -1);
	ft_replace_directory(export);
	dir = NULL;
	return (0);
}

int	ft_cd(t_cmd *cmd, t_env *export)
{
	char	*dir;
	char	*tmp;

	if (!cmd->args[1] || (cmd->args[1][0] == '~'
		&& ft_strlen(cmd->args[1]) == 1))
	{
		tmp = ft_search_in_list(export, "HOME=");
		if (!tmp)
			return (ft_putstr_fd("HOME not found\n", 2), 1);
		dir = &tmp[5];
	}
	else if (cmd->args[1][0] == '.' && !getcwd(NULL, sizeof(NULL)))
		return (ft_putstr_fd("cd :error retrieving current directory\n", 1), 1);
	else if (cmd->args[1][0] == '-')
	{
		tmp = ft_search_in_list(export, "OLDPWD");
		if (!tmp)
			return (ft_putstr_fd("OLDPWD not found\n", 2), 1);
		dir = &tmp[7];
	}
	else
		dir = cmd->args[1];
	if (change_directory(dir, export) == -1)
		return (1);
	return (0);
}
