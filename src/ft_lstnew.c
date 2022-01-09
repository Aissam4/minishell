/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:17:29 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/04 16:02:16 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_export	*ft_lstnew(void *content)
{
	t_export	*new;

	new = (t_export *)malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->variable = content;
	new->next = NULL;
	return (new);
}

t_words	*ft_lstnew_words(void *content)
{
	t_words	*new;

	new = (t_words *)malloc(sizeof(t_words));
	if (!new)
		return (NULL);
	new->words = content;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_lstnew_cmd(char **content)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = content;
	new->next = NULL;
	return (new);
}

t_files	*ft_lstnew_files(void *content, int type)
{
	t_files		*new;

	new = (t_files *)malloc(sizeof(t_files));
	if (!new)
		return (NULL);
	new->filename = content;
	new->type = type;
	new->next = NULL;
	return (new);
}
