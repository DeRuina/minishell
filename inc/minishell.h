/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/05 19:23:35 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h> 
	// please don't move this. It needs to be here. Otherwise it wont build on linux.
# include <stdlib.h> // getenv
# include <string.h>
/* #include <sys/syslimits.h>*/
# include <limits.h>       // this should work in linux
# include <linux/limits.h> // need it for PATH_MAX in linux
# include <sys/wait.h>     // for linux
# include <unistd.h>

# define IN 0
# define OUT 1

typedef struct s_node
{
	char			**full_cmd;
	int				pid;
	int				infile;
	int				outfile;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

enum				e_builtins
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

// exec
t_node				*ft_parse_args(char *line, t_vec env);
int					ft_child(t_node *node, t_vec envv);
int					ft_executor(t_node *node, t_vec envv);
int					builtin_commands(char **cmd, t_vec envv);

// Env
int					ft_putenv(t_vec *envs_vec, char *str);
int					ft_putenv_key(t_vec *envs_vec, char *key, char *str);
char				*ft_getenv(t_vec envs_vec, char *key);
t_vec				ft_copyenv(char *env[]);
char				**ft_strenv(t_vec envs_vec);

// Parsing
char				**ft_cmd_trim(char *line);
void				ft_expand(t_vec vars, char **line);
char				**ft_split_operators(char **array);
char				**ft_str_trim(char **array);
// expand

void				ft_expand(t_vec env_vars, char **arr);
// char			*ft_var_end(char *str);
// char			*ft_var_expand(t_vec env_vars, char *str);
char				*ft_expand_token(t_vec env_vars, char *str);

// expand utils
// void			ft_tmp_to_result(char **result, char **tmp);
// int				ft_should_expand_tilde(char *token, char *token_init);

// split_operators

char				**ft_split_operators(char **array);
char				**ft_str_trim(char **array);

// cmd_trim
char				*allocate_token(char *token_start, char *token_end);
int					find_closing_quote(char *quote, int *closing_quote,
						char **line);
void				handle_quotes(char **line);
char				*next_token_from_line(char **line);
int					cmd_trim_len(char *line);

// split_operators
char				**divide_into_array(char **array, char **answer);
char				*no_operator(char *array);
char				*malloc_new_token(char **array);
int					get_next_token(char **string);
int					check_operators_num_in_string(char *array);
int					split_operators_len(char **array);
int					is_token_an_operator(char **str);

// str_trim
char				*check_for_trim(char *str);
int					is_trim_needed(char *str);
char				*trim_token(char *str, char *answer, int i, char quote);
int					token_is_double_quotes(char *str);

// fd_handler
t_node				*ft_fd_handler(char **array, t_node *node,
						int *error_here_docs, int node_counter);
void				find_and_open_fds(char **array);
int					here_doc(char *delimiter);
int					here_doc_invalid_infile(char **array, int i,
						int **error_here_docs, int node_counter);
int					reopen_file_and_check(char *name);
int					get_infile_fd(char **array, int error_here_doc,
						char *infile);
int					get_outfile_fd(char **array, char *outfile);
char				*find_last_infile(char **array);
char				*find_last_outfile(char **array);
int	check_for_invalid_file_before_infile(char **array,
											int **error_here_docs,
											int node_counter);

// exec_path
char				*ft_get_exec_path(t_vec env, char *cmd);

// utils
// int				ft_max(int a, int b);
void				ft_pexit(char *error_msg);
int					is_builtin(char *cmd);

// node funtions
t_node				*new_node(char ***array, t_vec env, int *error_here_docs,
						int node_counter);
char				**get_node_cmd(char ***array);
int					cmd_len(char **array);
void				case_only_redirections(char ***array);
void				free_nodes(t_node *node);

// piper
int					**piper(char *array, t_node *node);
int					**allocate_pipes(char *array);
int					num_of_pipes(char *array);
void	change_infile_outfile_to_pipes(t_node *node,
									int **pipe_nbr);
void				free_pipes(int **pipe_nbr, char *array);

// Builtinså

void				ft_echo(char **full_cmd);
void				ft_exit(void);
void				ft_pwd(void);
char				*get_path(void);
void				ft_cd(char **full_cmd, t_vec *envs);
void				ft_env(t_vec envs);
void				ft_export(char **full_cmd, t_vec *envs);
void				export_no_arg(t_vec *envs);
void				ft_unset(t_vec *envs, char **full_cmd);

#endif
