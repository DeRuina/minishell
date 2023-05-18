/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/18 12:04:28 by druina           ###   ########.fr       */
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
char			*allocate_token(char *token_start, char *token_end);
int				find_closing_quote(char *quote, int *closing_quote,
					char **line);
void			handle_quotes(char **line);
char			*next_token_from_line(char **line);
int				cmd_trim_new_array_len(char *line);

// split_operators
char			**divide_into_array(char **array, char **answer);
char			*no_operator(char *array);
char			*malloc_new_token_and_move_pointer_to_next(char **array);
int				pointer_to_next_token_return_len(char **string);
int				check_operators_num_in_string(char *array);
int				split_operators_new_array_len(char **array, int i);

// str_trim
char			*check_for_trim(char *str);
char			*null_term_and_free(char *answer, int i, char *temp);
char			*trim_loop(char *str, char *answer, int i, char *c);
char			*handle_trim_only_quotes_case(char *str, char *answer);

// fd_handler
int				*find_and_open_fds(char **array, int *fds, int i, int *flag);
int				here_doc(char *delimiter);
void			here_doc_if_invalid_infile(char **array, int i, int bad_fd);
int				get_infile_fd(char **array, int *flag);
char			*find_infile_outfile(char **array, char *operator1,
					char *operator2, int i);
void			error_fd(int fd, char *array, char *error);

// utils
int				ft_max(int a, int b);

// node funtions
t_node			*new_node_and_link(char ***array, int *flag);
char			**get_node_cmd(char ***array);
int				len_node_cmd(char **array);
void			case_only_redirections(char ***array);

#endif
