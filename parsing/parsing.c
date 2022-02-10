/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:26:08 by atouhami          #+#    #+#             */
/*   Updated: 2022/02/07 17:55:53 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command(t_cmd *list, t_cmd	*tmp)
{
	int		i;

	while (list)
	{
		i = 0;
		tmp = list;
		if (list->command)
			free(list->command);
		free_arguments(list);
		if (list->files_nb)
		{
			while (i < list->files_nb)
				free(list->files[i++].filename);
			free(list->files);
		}
		free_wildcard(list);
		list = list->next;
		free(tmp);
	}
}

t_cmd	*cmd_list_create(t_cmd *previous_last)
{
	t_cmd	*list;

	list = malloc(sizeof(t_cmd));
	if (!list)
		return (printf("failed allocation"), exit(1), NULL);
	if (previous_last)
		previous_last->next = list;
	list->next = NULL;
	list->previous = previous_last;
	return (list);
}

void	assign_command(int *count_args, int *count_files
	, t_cmd *cmd, t_tokens *list)
{
	cmd->args = NULL;
	cmd->files = NULL;
	cmd->command = NULL;
	*count_args = count_elements(list, STRING) + 1;
	if (*count_args > 0)
	{
		cmd->args = malloc(sizeof(char *) * *count_args + 2);
		if (!cmd->args)
			return (printf("failed allocation"), exit(1));
		cmd->args[*count_args] = NULL;
	}
	*count_files = count_elements(list, FILE);
	if (*count_files > 0)
	{
		cmd->files = malloc(sizeof(t_files) * *count_files);
		if (!cmd->files)
			return (printf("failed allocation"), exit(1));
	}
}

void	fill_command(t_tokens *list, t_cmd *cmd,
		int count_args, int count_files)
{
	int	i;
	int	f_nb;

	assign_command(&count_args, &count_files, cmd, list);
	set_to_value(&i, &f_nb);
	cmd->files_nb = count_files;
	while (list->type != PIPE && list->type != AND && list->next)
	{
		fill_cmd_name_wild(list, cmd);
		if (list->type == STRING)
				cmd->args[i++] = get_arg(list);
		if (list->type == FILE)
		{
			cmd->files[f_nb].is_double = 0;
			cmd->files[f_nb].filename = list->filename;
			cmd->files[f_nb].type = list->previous->redirection_type;
			if (list->previous->previous->type == REDIRECTION)
				cmd->files[f_nb].is_double = 1;
			f_nb++;
		}
		list = list-> next;
	}
	cmd->arguments = merge_args(cmd->args, cmd->wildcard_arguments);
}

void	parse_to_command(t_tokens *list, t_cmd *cmd, t_cmd*head)
{
	t_pipe	pipe_;

	cmd = cmd_list_create(NULL);
	head = cmd;
	while (list->next)
	{
		while ((list->type == PIPE || list->type == AND) && list->next)
			list = list-> next;
		cmd->wildcard_arguments = NULL;
		cmd->arguments = NULL;
		define_next_operation(list, cmd);
		fill_command(list, cmd, 0, 0);
		cmd->env = list->env;
		while (list->type != PIPE && list->type != AND && list->next)
			list = list-> next;
		if (list->next)
		{
			cmd_list_create(cmd);
			cmd = cmd->next;
		}
	}
	parse_dollar_signe(head, cmd->env);
	ft_execution(&pipe_, head, head->env);
	free_command(head, NULL);
}
