/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/04 16:27:42 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

// Env

int			ft_putenv(t_vec *envs_vec, char *str);
char		*ft_getenv(t_vec envs_vec, char *key);
char		*ft_getkey(char *str);
char		*ft_getvalue(char *str);

// cmd_trim

char		**ft_cmd_trim(char *line);

// expand

void		ft_expand(t_vec env_vars, char **arr);
char		*ft_var_end(char *str);
char		*ft_var_expand(t_vec env_vars, char *str);
char		*ft_expand_token(t_vec env_vars, char *str);

// split_operators

char		**ft_split_operators(char **array);
char		**ft_str_trim(char **array);

// cmd_trim
char		*malloc_token(char *start, char *line);
int			quotes_cases(char first, char character, int *flag, char **line);
void		handle_quotes(char *whitespace, char **line);
char		*get_token(char **line);

// split_operators
char		**divide_into_arr(char **array, char **answer);
void		*no_op(char **answer, char **array, int *offset, int *i);
char		*malloc_new_token(char **array);
int			len_to_token(char **array, int *flag);
int			check_for_operator(char *array);
int			find_proper_allocation(char **array, int i);
void		get_allocation_num(char *array, int *count);

// str_trim
char		*check_for_trim(char *str);
char		*null_term_and_free(char *answer, int i, char *temp);
char		*trim_loop(char *str, char *answer, int i, char *c);

#endif
