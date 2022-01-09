/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 15:24:09 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/08 00:35:12 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_double_quotes(char *var)
{
	int		count;
	int		index;
	char	*finall_var;

	count = 0;
	index = 0;
	finall_var = (char *)malloc(sizeof(char) * ft_strlen(var) + 3);
	if (!finall_var)
		return (NULL);
	while (var[count] && var[count] != '=')
		count++;
	count++;
	ft_memmove(finall_var, var, count);
	finall_var[count] = '\"';
	index = count + 1;
	while (var[count])
		finall_var[index++] = var[count++];
	finall_var[index] = '\"';
	finall_var[index + 1] = '\0';
	return (finall_var);
}

void	ft_export_init(char *var, t_export *export, int exec_print)
{
	t_export	*new;

	new = ft_lstnew(var);
	if (exec_print == 1)
		new->print_exec = 1;
	else
		new->print_exec = 0;
	ft_lstadd_back(export, new);
}

void	print_export(t_export *export)
{
	while (export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(set_double_quotes(export->variable), 1);
		ft_putchar_fd('\n', 1);
		export = export->next;
	}
}

int	ft_export(t_cmd *cmd, t_export *export)
{
	int		i;

	i = -1;
	if (!cmd->args[1])
		print_export(export);
	else if (cmd->args[1] && ft_isdigit(cmd->args[1][0]))
	{
		printf("%s : not a valid identifier\n", cmd->args[1]);
		return (1);
	}
	else if (cmd->args[1])
	{
		cmd->args = &cmd->args[1];
		while (cmd->args[++i])
		{
			if (ft_strchr(cmd->args[i], '='))
				ft_export_init(cmd->args[i], export, 1);
			else
				ft_export_init(cmd->args[i], export, 0);
		}
		parse_dollar_signe(cmd, export);
	}
	return (0);
}
