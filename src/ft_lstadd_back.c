/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:36:07 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/05 05:48:12 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_export *lst, t_export *new)
{
	t_export	*tmp;

	tmp = lst;
	if (lst == NULL)
		lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		tmp = NULL;
	}
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->next = NULL;
		tmp->next = new;
	}
}

void	ft_lstadd_back_words(t_words **lst, t_words *new)
{
	t_words	*tmp;

	tmp = *lst;
	if (!*(new->words))
	{
		free(new->words);
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->next = NULL;
		tmp->next = new;
	}
}

void	ft_lstadd_back_file(t_files **lst, t_files *new)
{
	t_files	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->next = NULL;
			tmp->next = new;
	}
}
