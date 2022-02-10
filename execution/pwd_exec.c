/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:23:01 by abarchil          #+#    #+#             */
/*   Updated: 2022/02/09 03:10:05 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	buff[1024];
	char	*dir;

	if (cmd->args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		g_tools.exit_status = 256;
		return (1);
	}
	dir = getcwd(buff, sizeof(buff));
	if (!dir)
	{
		ft_putstr_fd(buff, 1);
		ft_putchar_fd('\n', 1);
		return (-1);
	}
	ft_putstr_fd(dir, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
