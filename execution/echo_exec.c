/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 05:27:02 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/08 00:34:07 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_args(t_cmd *cmd, int index)
{
	while (cmd->args[++index])
	{
		ft_putstr_fd(cmd->args[index], 1);
		if (cmd->args[index + 1])
			ft_putchar_fd(' ', 1);
	}
}

int	ft_echo(t_cmd *cmd)
{
	int		new_line;
	int		index;

	new_line = 0;
	index = -1;
	if (!cmd->args[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == 'n')
	{
		new_line = 1;
		index = 1;
	}
	else
		index = 0;
	print_args(cmd, index);
	if (new_line == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
