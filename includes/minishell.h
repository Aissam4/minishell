/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-boua <fel-boua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:54:20 by fel-boua          #+#    #+#             */
/*   Updated: 2022/01/08 02:21:58 by fel-boua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# define GREEN "\e[0;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define TRUE 1
# define YES 1
# define FALSE 0
# define NO 0
# define W 1
# define R 0
# define PIPE -1
# define REDIRECTION_IN -2
# define REDIRECTION_OUT -3
# define REDIRECTION_OUT_APPEND -4
# define HER_DOC -5
# define DOLLAR_SIGNE -6
# define DELIMITER -7
# define DOUBLE_QUOTES -8
# define SINGLE_QUOTES -9

typedef struct s_tools
{
	int		is_runnig;
	int		exit_status;
	char	*command;
}	t_tools;

t_tools	g_tools;

typedef struct t_export
{
	char						*variable;
	int							print_exec;
	struct t_export				*next;
}	t_export;

typedef struct s_words
{
	char			*words;
	struct s_words	*next;
}	t_words;

typedef struct s_files
{
	int				type;
	int				fd;
	char			*filename;
	struct s_files	*next;

}	t_files;

typedef struct s_cmd
{
	char				*command;
	int					red_pipe;
	char				**args;
	t_files				*files;
	struct s_cmd		*next;
}					t_cmd;

typedef struct s_pipe
{
	pid_t	pid;
	int		pipefd[2];
}	t_pipe;

/**************** SOURCES ***************/

void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strlen_2d(char **s);
char		*get_next_line(int fd);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strchr_index(char *s, int c);
char		*remchar(char *s, char c);
int			ft_isalpha(int c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(char const *s, size_t start, size_t len);
int			ft_atoi(const char *str);
char		*ft_strndup(const char *s, int n);
void		ft_free_2d(char **av);
int			ft_isdigit(int c);
char		*ft_itoa(int n);

/****** linked list *********/

int			ft_lstsize(t_cmd *lst);
t_export	*ft_lstnew(void *content);
void		ft_del_node_cmd(t_cmd *lst);
void		ft_clear_list(t_words *words);
void		ft_clear_list_cmd(t_cmd *cmd);
void		ft_clear_list_export(t_export *export);
t_cmd		*ft_lstnew_cmd(char **content);
t_words		*ft_lstnew_words(void *content);
int			ft_lstsize_export(t_export *lst);
void		ft_del_node(t_export *lst, char *content);
t_files		*ft_lstnew_files(void *content, int type);
void		ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void		ft_lstadd_back(t_export *lst, t_export *new);
void		ft_lstadd_back_words(t_words **lst, t_words *new);
void		ft_lstadd_back_file(t_files **lst, t_files *new);
char		*ft_search_in_list(t_export *export, char *name);

/************* minishell *****************/

/******** builtins *******/

int			ft_pwd(t_cmd *cmd, t_export *export);
int			ft_cd(t_cmd *cmd, t_export *export);
int			ft_echo(t_cmd *cmd);
int			ft_exit(t_cmd *cmd);
int			ft_export(t_cmd *cmd, t_export *export);
int			ft_unset(t_cmd *cmd, t_export *export);
int			ft_env(t_export *export);

/********** lixing **********/

char		*lexing(char *command, int **lampe);
int			check_lexing_syntax(char *command);
int			checke_near_token(char *command);
int			lexing_first_char(char *command);
int			lexing_last_char(char *command);
int			check_quotes(char *command);
void		lexing_2(char *command, int count, int **lampe);
void		set_db_quotes(char *command, int **lampe, int count);
void		set_sb_quotes(char *command, int **lampe, int count);
void		set_here_doc_quotes(char *command, int count);
void		set_ro_app_quotes(char *command, int count);

/******** parsing *******/

int			dollar_signe_search(t_cmd *cmd);
int			check_if_builting(char *command);
void		multi_redirection(t_cmd *cmd);
int			red_in(t_cmd *cmd);
char		**delete_array(char **av);
void		handling_input(t_cmd *cmd);
char		*set_double_quotes(char *var);
void		print_export(t_export *export);
char		*get_var_value(char *variable);
char		**lst_to_array(t_export *export);
t_cmd		*parsing(t_words *words, t_cmd *cmd);
char		*get_var(char *var, t_export *export);
t_words		*parsing_word(char *command, t_words *cmds);
int			check_command(t_cmd *cmd, t_export *export);
void		check_command_error(t_cmd *cmd, t_export *export,
				char *command, char **env);
t_cmd		*parse_commands(t_words *words, t_cmd *cmd);
void		environment_init(char **env, t_export *export);
void		parse_dollar_signe(t_cmd *cmd, t_export *export);
void		parsing_export_command(char *command, t_export *export);
void		ft_export_init(char *var, t_export *export, int exec_print);

/********* EXECUTION *************/

void		ft_execution(t_pipe *pipe_, t_cmd *cmd, t_export *export);
void		execute_command(t_pipe *pipe_, t_cmd *cmd, t_export *export);
void		ft_one_command(char **env, t_pipe *pipe_, t_cmd *cmd);
char		*ft_check_excute(t_cmd *cmd, char **env);
char		*ft_check_path(char **env);
void		ft_replace_directory(t_export *export);
void		replace_pwd(t_export *export);
void		ft_here_doc(t_cmd *cmd);

/********* SIGNEL *************/
void		sigint_handler(int sig);
void		signals(void);

#endif
