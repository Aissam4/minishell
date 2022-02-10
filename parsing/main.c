/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:00:49 by atouhami          #+#    #+#             */
/*   Updated: 2022/02/10 08:33:59 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cast_to_void(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*envirements;

	cast_to_void(argc, argv);
	if (!env[0])
		envirements = env_list(NULL);
	else
		envirements = env_list(env);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		g_tools.g_status = 0;
		line = readline("\e[1;32m➜  \e[1;36mMinishell\e[1;33m ➤ \e[0;37m");
		if (!line)
			return (free_env(envirements),
				rl_clear_history(), printf("exit\n"), 0);
		add_history(line);
		take_command(line, envirements);
		free(line);
	}
}
