/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-boua <fel-boua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:06:48 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/05 07:18:32 by fel-boua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize(t_cmd *lst)
{
	int		size;
	t_cmd	*new;

	new = lst;
	size = 0;
	while (new)
	{
		size++;
		new = new->next;
	}
	return (size);
}

int	ft_lstsize_export(t_export *lst)
{
	int			size;
	t_export	*new;

	new = lst;
	size = 0;
	while (new)
	{
		size++;
		new = new->next;
	}
	return (size);
}
