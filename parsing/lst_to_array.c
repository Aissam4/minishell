/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-boua <fel-boua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 07:17:17 by fel-boua          #+#    #+#             */
/*   Updated: 2022/01/05 08:35:32 by fel-boua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**lst_to_array(t_export *export)
{
	int			len;
	int			index;
	char		**arr;
	t_export	*new;

	index = 0;
	new = export;
	len = ft_lstsize_export(export);
	arr = (char **)malloc(sizeof(char *) * len + 1);
	if (!arr)
		return (NULL);
	while (new)
	{
		arr[index] = ft_strdup(new->variable);
		new = new->next;
		index++;
	}
	arr[index] = NULL;
	new = NULL;
	return (arr);
}
