/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 17:59:42 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 14:34:57 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *export)
{
	while (export)
	{
		if (export->does_have_value == 1)
		{
			ft_putstr_fd(export->str, 1);
			ft_putchar_fd('\n', 1);
			export = export->next;
		}
		else
			export = export->next;
	}
	return (0);
}
