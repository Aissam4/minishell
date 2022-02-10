/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:00:57 by atouhami          #+#    #+#             */
/*   Updated: 2022/02/10 08:18:45 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**** includes ****/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
/**** defines ****/
# define FILE -2
# define COMMAND -1
# define STRING 0
# define WILDCARD 1
# define PIPE 2
# define AND 3
# define REDIRECTION 4
# define TRUE 1
# define W 1
# define R 0
# define DOLLAR_SIGNE -9
/******** global struct *******/

typedef struct s_tools
{
	int		is_runnig;
	int		exit_status;
	int		g_status;
}	t_tools;

t_tools	g_tools;

/**** structs ****/
typedef struct s_env
{
	struct s_env	*next;
	int				does_have_value;
	char			*str;
}	t_env;

typedef struct s_pipe
{
	int		pipefd[2];
	pid_t	pid;
}	t_pipe;

typedef struct s_tokens
{
	struct s_tokens	*next;
	struct s_tokens	*previous;
	t_env			*env;
	int				type;
	int				lenght;
	int				credit;
	int				redirection_type;
	char			*str;
	char			*filename;
}	t_tokens;

typedef struct s_files
{
	int		type;
	int		is_double;
	int		fd;
	char	*filename;
}	t_files;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*previous;
	t_files			*files;
	t_files			heredoc;
	t_env			*env;
	int				files_nb;
	int				next_operation;
	char			*command;
	char			**args;
	char			**wildcard_arguments;
	char			**arguments;
}	t_cmd;

/***** operations *****/

# define OP_NONE 0
# define OP_PIPE 1
# define OP_OR 2
# define OP_AND 3
/***** Srcs *******/

int			get_index(char *str, char c);
int			ft_isdigit(int c);
void		*ft_memcpy(void *dest, const void *src, int n);
int			ft_atoi(const char *str);
int			ft_memcmp(const void *s1, const void *s2, int n);
char		*ft_substr_2(char const *s, int start, int len);
char		*ft_strjoin_2(char const *s1, char const *s2);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
t_env		*ft_lstnew(void *content);
void		ft_lstadd_back(t_env *lst, t_env *new);
void		ft_free_2d(char **av);
char		**ft_split(char const *s, char c);
int			ft_lstsize(t_cmd *lst);
int			ft_lstsize_export(t_env *lst);
void		*ft_calloc(int count, int size);
int			ft_strlen_2d(char **s);
void		ft_free_env(char **av);
char		*ft_itoa(int n);
/**parsing dollar signe ****/
void		free_dollar_sign_utils(int index, t_cmd *cmd,
				char *tmp_arg, char **var);
void		parse_dollar_signe(t_cmd *cmd, t_env *export);
char		*ft_strtrim(char *s1, char *set);

/****** execution ******/

void		finish_execution(char **env);
void		reset_fd(int savefd[2]);
void		signal_exit_code(void);
void		preexec(int pipe[2]);
void		postexec(int pipe[2]);
int			execute_cmd(t_cmd **cmd, t_pipe *pipe_, \
				int savefd[2], t_env *export);
int			operation_etiration(t_cmd *cmd, t_pipe *pipe_, \
				int savefd[2], t_env *export);
void		creat_process(t_cmd *cmd, t_pipe *pipe_, \
				int savefd[2], t_env *export);
int			operations(t_cmd *cmd, t_pipe *pipe_, \
				int savefd[2], t_env *export);
void		child_process(t_cmd *cmd, t_pipe *pipe_, \
				char **env, char *command);
void		parent_process(t_cmd *cmd, t_pipe *pipe_, \
				int save[2], char *command);
int			creat_pipe(t_cmd *cmd, t_pipe *pipe_, \
				char **env, int savefd[2]);
int			check_builtins(t_cmd *cmd, char **env, \
				t_env *export, t_pipe *pipe_);
void		and_or_operation(t_cmd *cmd, t_env *export, \
t_pipe *pipe_, char **env);
void		builting_child(t_pipe *pipe_, t_cmd *cmd, t_env *export);
void		decrement_go_next(int *cmd_count, t_cmd **cmd);
void		ft_env_init(char *var, t_env *export, int exec_print);
void		print_env(t_env *export);
void		ft_execution(t_pipe *pipe_, t_cmd *cmd, t_env *export);
void		execute_command(t_pipe *pipe_, t_cmd *cmd, t_env *export);
void		ft_one_command(char **env, t_pipe *pipe_, t_cmd *cmd);
char		*ft_check_excute(t_cmd *cmd, char **env);
char		*ft_check_path(char **env);
void		ft_here_doc(t_cmd *cmd, int i);
int			red_in(t_cmd *cmd, int i);
void		multi_redirection(t_cmd *cmd, int i);
int			ft_pwd(t_cmd *cmd);
int			ft_unset(t_cmd *cmd, t_env *export);
void		ft_del_node(t_env *lst, char *content);
char		*get_next_line(int fd);
void		ft_bzero(void *s, int n);
void		*ft_memset(void *s, int c, int n);
char		**lst_to_array(t_env *export);
void		check_command_error(t_cmd *cmd, t_env *export,
				char *command, char **env);

void		replace_pwd(t_env *export);
char		*ft_search_in_list(t_env *export, char *name);
int			check_cd_exit(t_cmd *cmd, t_env *env);
void		ft_replace_directory(t_env *export);
int			ft_cd(t_cmd *cmd, t_env *export);
int			check_if_builting(char *command);
int			check_command(t_cmd *cmd, t_env *export);
int			ft_echo(t_cmd *cmd);
int			ft_env(t_env *export);
int			ft_isnumber(char *numbder);
int			ft_export(t_cmd *cmd, t_env *export);
int			ft_exit(t_cmd *cmd);

/**** functions ****/

char		*get_arg(t_tokens *list);
void		fill_list(t_tokens *list, char *str, t_env *env, int was_in_while);
void		lexer_assign(t_tokens *head, t_tokens *next,
				char *str, t_env *env);
void		free_all(t_tokens *head);
int			check_types(t_tokens *list);
int			lexer(char *str, t_env *env);
char		*ft_strchr(char *string, int searchedChar);
char		*ft_substr(char const *s, int start, int len);
void		handler(int sig);
int			starts_with(char *str, char *tofind);
int			verifiy_quotes(char *line, char c, char ignore);
int			verify_errors(char *line);
t_tokens	*list_create(t_tokens *previous_last);
int			skip_quotes(char *str, int i, char c);
void		define_type(char *str, int i, t_tokens *list);
void		fill_infos(char *str, int i, t_tokens *list, t_env *env);
void		take_command(char *str, t_env *env);
int			ft_strlen(const char *s);
void		*ft_memmove(void *dest, const void *src, int n);
char		*ft_strdup(const char *source);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
t_env		*env_list_create(t_env*previous_last, char *str);
t_env		*env_list(char *env[]);
void		free_env(t_env *list);
void		parse_to_command(t_tokens *list, t_cmd *cmd, t_cmd *head);
int			count_elements(t_tokens *list, int element);
void		set_to_value(int *i, int *f_nb);
void		define_next_operation(t_tokens *list, t_cmd *cmd);
int			check_types_two(t_tokens *list);
void		free_wildcard(t_cmd *list);
char		**wildcard(char **wildcard);
char		**merge_args(char **arguments, char **wildcard);
void		fill_cmd_name_wild(t_tokens *list, t_cmd *cmd);
void		free_arguments(t_cmd *list);
/**** DEBUG ****/
void		debug_print_list(t_tokens *list);
void		debug_print_env(t_env *list);
void		debug_printf_command(t_cmd *list);
#endif
