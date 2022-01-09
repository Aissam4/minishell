/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:23:01 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/08 00:34:45 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_cmd *cmd, t_export *export)
{
	char	*buf;

	buf = NULL;
	if (cmd->args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		return (1);
	}
	while (export)
	{
		if (!ft_memcmp(export->variable, "PWD=", 4))
			break ;
		export = export->next;
	}
	ft_putstr_fd(remchar(&export->variable[4], '\"'), 1);
	ft_putchar_fd('\n', 1);
	free(buf);
	buf = NULL;
	return (0);
}
