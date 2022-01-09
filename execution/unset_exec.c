/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:29:07 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/08 00:35:22 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_cmd *cmd, t_export *export)
{
	int		i;

	i = -1;
	if (!cmd->args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	else
	{
		while (cmd->args[++i])
			ft_del_node(export, cmd->args[i]);
		return (0);
	}
}
