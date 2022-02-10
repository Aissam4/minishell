/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:04:36 by atouhami          #+#    #+#             */
/*   Updated: 2022/01/13 11:37:11 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_list_create(t_env*previous_last, char *str)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (printf("failed allocation"), exit(1), NULL);
	list->str = ft_strdup(str);
	list->does_have_value = 0;
	if (ft_strchr(str, '='))
		list->does_have_value = 1;
	if (previous_last)
		previous_last->next = list;
	list->next = NULL;
	return (list);
}

t_env	*env_list(char *env[])
{
	t_env	*head;
	t_env	*next;
	int		i;

	i = 2;
	if (env && env[0])
	{
		head = env_list_create(NULL, env[0]);
		next = env_list_create(head, env[1]);
		while (env[i])
			next = env_list_create(next, env[i++]);
	}
	else
		head = env_list_create(NULL, "");
	return (head);
}

void	free_env(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
		free(tmp);
	}
}
