/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_signe_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:35:11 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/16 17:36:40 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_dollar_sign_utils(int index, t_cmd *cmd, char *tmp_arg, char **var)
{
	int	i;

	i = -1;
	free(cmd->arguments[index]);
	cmd->arguments[index] = ft_strdup(tmp_arg);
	free(tmp_arg);
	i = -1;
	while (var[++i])
		cmd->arguments[index] = ft_strjoin(cmd->arguments[index], var[i]);
	ft_free_env(var);
}
