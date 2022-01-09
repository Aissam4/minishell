/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-boua <fel-boua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 07:15:57 by fel-boua          #+#    #+#             */
/*   Updated: 2022/01/08 02:41:47 by fel-boua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_words	*parsing_word(char *command, t_words *cmds)
{
	int		count;
	int		last_index;

	count = 0;
	last_index = count;
	while (command[count])
	{
		last_index = count;
		while (command[count] && command[count] != PIPE)
			count++;
		ft_lstadd_back_words(&cmds,
			ft_lstnew_words(ft_substr
				(command, last_index, count - last_index)));
		count++;
	}
	return (cmds);
}

static void	cmd_init(t_cmd *cmd, int i)
{
	if (cmd->args[i][0] == REDIRECTION_IN
		|| cmd->args[i][0] == REDIRECTION_OUT
		|| cmd->args[i][0] == REDIRECTION_OUT_APPEND
		|| cmd->args[i][0] == HER_DOC)
	{
		if (cmd->args[i][0] == REDIRECTION_IN)
			ft_lstadd_back_file(&cmd->files,
				ft_lstnew_files(ft_strdup(cmd->args[i + 1]), 2));
		else if (cmd->args[i][0] == REDIRECTION_OUT)
			ft_lstadd_back_file(&cmd->files,
				ft_lstnew_files(ft_strdup(cmd->args[i + 1]), 3));
		else if (cmd->args[i][0] == REDIRECTION_OUT_APPEND)
			ft_lstadd_back_file(&cmd->files,
				ft_lstnew_files(ft_strdup(cmd->args[i + 1]), 4));
		else if (cmd->args[i][0] == HER_DOC)
			ft_lstadd_back_file(&cmd->files,
				ft_lstnew_files(ft_strdup(cmd->args[i + 1]), 5));
		i++;
	}
	if (cmd->args[i][0] == DOUBLE_QUOTES)
		cmd->args[i] = remchar(cmd->args[i], DOUBLE_QUOTES);
	if (cmd->args[i][0] == SINGLE_QUOTES)
		cmd->args[i] = remchar(cmd->args[i], SINGLE_QUOTES);
}

t_cmd	*parse_commands(t_words *words, t_cmd *cmd)
{
	int	i;

	i = -1;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->files = NULL;
	cmd->args = ft_split(words->words, DELIMITER);
	if (!cmd->args[0])
		return (cmd);
	if (cmd->args[0][0] > 0)
		cmd->command = ft_strdup(cmd->args[0]);
	else if ((cmd->args[0][0] < 0 && cmd->args[0][0] != DELIMITER)
		&& ft_strlen(words->words) > 1)
		cmd->command = ft_strdup(cmd->args[2]);
	while (cmd->args[++i])
		cmd_init(cmd, i);
	cmd->args = delete_array(cmd->args);
	return (cmd);
}

t_cmd	*parsing(t_words *words, t_cmd *cmd)
{
	while (words)
	{
		ft_lstadd_back_cmd(&cmd, parse_commands(words, cmd));
		words = words->next;
	}
	return (cmd);
}

char	**delete_array(char **av)
{
	int		index;
	int		tmp_av_index;
	char	**tmp_av;

	index = 0;
	tmp_av_index = 0;
	tmp_av = (char **)malloc(sizeof(char *) * ft_strlen_2d(av) - 1);
	if (!tmp_av)
		return (NULL);
	while (av[index])
	{
		if ((av[index][0] < 0 && av[index][0] > -6) && av[index + 2])
			index += 2;
		else if ((av[index][0] < 0 && av[index][0] > -6) && !av[index + 2])
			break ;
		else
		{
			tmp_av[tmp_av_index] = ft_strdup(av[index]);
			tmp_av_index++;
			index++;
		}
	}
	tmp_av[tmp_av_index] = NULL;
	ft_free_2d(av);
	return (tmp_av);
}
