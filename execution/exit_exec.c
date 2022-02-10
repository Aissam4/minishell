/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 07:58:13 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 14:29:25 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_2d(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_isnumber(char *number)
{
	int	i;

	i = 0;
	if (number[i] == '-')
		i++;
	while (number[i])
	{
		if (!ft_isdigit(number[i]))
			exit(0);
		i++;
	}
	exit(1);
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd || ft_strlen_2d(cmd->arguments) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (ft_strlen_2d(cmd->arguments) > 2)
		ft_putstr_fd("exit: too many arguments\n", 1);
	else if (!ft_isnumber(cmd->arguments[1]))
	{
		printf("exit: %s: numeric argument required\n", cmd->arguments[1]);
		exit(255);
	}
	else
		exit(ft_atoi(cmd->arguments[1]));
	exit(0);
}
