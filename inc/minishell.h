/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/12 14:32:30 by druina           ###   ########.fr       */
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
# include <string.h>

typedef struct node
{
	char		**full_cmd;
	char		*path_name;
	int			pid;
	int			infile;
	int			outfile;
	struct node	*next_node;
}				t_node;

typedef struct s_env
{
	char		*key;
	char		*value;
}				t_env;

// Env
int				ft_putenv(t_vec *envs_vec, char *str);
char			*ft_getenv(t_vec envs_vec, char *key);
char			*ft_getkey(char *str);
char			*ft_getvalue(char *str);

// Parsing
char			**ft_cmd_trim(char *line);
void			ft_expand(t_vec vars, char **line);
char			**ft_split_operators(char **array);
char			**ft_str_trim(char **array);
t_node			*ft_parse_args(char **array);
int				*ft_fd_handler(char **array, int *flag);

// expand

void			ft_expand(t_vec env_vars, char **arr);
char			*ft_var_end(char *str);
char			*ft_var_expand(t_vec env_vars, char *str);
char			*ft_expand_token(t_vec env_vars, char *str);

// expand utils
void			ft_tmp_to_result(char **result, char **tmp);
int				ft_should_expand_tilde(char *token, char *token_init);

// split_operators

char			**ft_split_operators(char **array);
char			**ft_str_trim(char **array);

// cmd_trim
char			*allocate_token(char *start, char *line);
int				quotes_edge_cases(char first, char character, int *flag,
					char **line);
void			handle_quotes(char *whitespace, char **line);
char			*next_token_from_line(char **line);

// split_operators
char			**divide_into_array(char **array, char **answer);
void			*no_operator(char **answer, char **array, int *offset, int *i);
char			*malloc_new_token(char **array);
int				len_to_operator(char **array, int *flag);
int				check_for_operator(char *array);
int				find_new_array_len(char **array, int i);
void			get_allocation_len(char *array, int *count);

// str_trim
char			*check_for_trim(char *str);
char			*null_term_and_free(char *answer, int i, char *temp);
char			*trim_loop(char *str, char *answer, int i, char *c);
char			*handle_trim_only_quotes_case(char *str, char *answer);

// fd_handler
int				*find_and_open_fds(char **array, int *fds, int i, int *flag);
int				here_doc(char *delimiter);
void			here_doc_if_invalid_infile(char **array, int i);
int				get_infile_fd(char **array, int *flag);
char			*find_infile_outfile(char **array, char *operator1,
					char *operator2, int i);
void			error_fd(int fd, char **array, int i);

// utils
int				ft_max(int a, int b);

// node funtions
t_node			*new_node_and_link(char ***array, int *flag);
char			**get_node_cmd(char ***array);
int				len_node_cmd(char **array);
void			case_only_redirections(char ***array);

#endif
