/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:55:35 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/13 14:29:37 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_to_array(t_env *export)
{
	int			len;
	int			index;
	char		**arr;
	t_env		*new;

	index = 0;
	new = export;
	len = ft_lstsize_export(export);
	arr = (char **)malloc(sizeof(char *) * len + 1);
	if (!arr)
		return (printf("failed allocation"), exit(1), NULL);
	while (new)
	{
		arr[index] = ft_strdup(new->str);
		new = new->next;
		index++;
	}
	arr[index] = NULL;
	new = NULL;
	return (arr);
}
