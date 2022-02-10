/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 07:17:51 by fel-boua          #+#    #+#             */
/*   Updated: 2022/01/16 16:49:19 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_node(t_env *lst, char *content)
{
	t_env	*tmp;

	while (lst->next)
	{
		tmp = lst->next;
		if (!ft_memcmp(content, tmp->str, ft_strlen(content)))
		{
			lst->next = lst->next->next;
			free(tmp->str);
			tmp->str = NULL;
			free(tmp);
			tmp->next = NULL;
			tmp = NULL;
			return ;
		}
		lst = lst->next;
	}
}
