/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:29:07 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/10 08:40:36 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_cmd *cmd, t_env *export)
{
	int		i;

	i = -1;
	if (!cmd->args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	else if (cmd->arguments[1] && ft_isdigit(cmd->arguments[1][0]))
	{
		printf("%s : not a valid identifier\n", cmd->arguments[1]);
		return (1);
	}
	else
	{
		while (cmd->args[++i])
			ft_del_node(export, cmd->args[i]);
		return (0);
	}
}
