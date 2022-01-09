/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 03:07:05 by abarchil          #+#    #+#             */
/*   Updated: 2022/01/07 03:31:26 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_db_quotes(char *command, int **lampe, int count)
{
	if (lampe[0][2] == 1)
		lampe[0][2] = 0;
	else
		lampe[0][2] = 1;
	command[count] = DOUBLE_QUOTES;
}

void	set_sb_quotes(char *command, int **lampe, int count)
{
	if (lampe[0][2] == 1)
		lampe[0][2] = 0;
	else
		lampe[0][2] = 1;
	command[count] = SINGLE_QUOTES;
}

void	set_here_doc_quotes(char *command, int count)
{
	command[count] = HER_DOC;
	command[count + 1] = HER_DOC;
}

void	set_ro_app_quotes(char *command, int count)
{
	command[count] = REDIRECTION_OUT_APPEND;
	command[count + 1] = REDIRECTION_OUT_APPEND;
}

void	lexing_2(char *command, int count, int **lampe)
{
	if (command[count] == '>' && !lampe[0][1] && !lampe[0][2])
		command[count] = REDIRECTION_OUT;
	else if (command[count] == '<' && !lampe[0][1] && !lampe[0][2])
		command[count] = REDIRECTION_IN;
	else if ((command[count] == '$' && !lampe[0][1]) ||
		(command[count] == '$' && !lampe[0][1] && !lampe[0][2]))
		command[count] = DOLLAR_SIGNE;
	else if (command[count] == ' ' && !lampe[0][1] && !lampe[0][2])
		command[count] = DELIMITER;
	else if (command[count] == '\"')
		set_db_quotes(command, lampe, count);
	else if (command[count] == '\'')
		set_sb_quotes(command, lampe, count);
}
