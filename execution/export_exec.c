/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 15:24:09 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 14:44:43 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_init(char *var, t_env *export, int exec_print)
{
	(void)exec_print;
	while (export->next)
		export = export->next;
	env_list_create(export, var);
}

void	print_env(t_env *export)
{
	while (export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(export->str, 1);
		ft_putchar_fd('\n', 1);
		export = export->next;
	}
}

int	ft_export(t_cmd *cmd, t_env *export)
{
	int		i;

	i = 0;
	if (!cmd->arguments[1])
		print_env(export);
	else if (cmd->arguments[1] && ft_isdigit(cmd->arguments[1][0]))
	{
		printf("%s : not a valid identifier\n", cmd->arguments[1]);
		return (1);
	}
	else if (cmd->arguments[1])
	{
		while (cmd->arguments[++i])
		{
			if (ft_strchr(cmd->arguments[i], '='))
				ft_env_init(cmd->arguments[i], export, 1);
			else
				ft_env_init(cmd->arguments[i], export, 0);
		}
	}
	return (0);
}
