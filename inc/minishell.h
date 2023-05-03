/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/03 17:36:24 by tspoof           ###   ########.fr       */
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

// split_operators

char		**ft_split_operators(char **array);

// Let's order this stuff in some logical manner

char		*malloc_token(char *start, char *line);
int			quotes_cases(char first, char character, int *flag, char **line);
void		handle_quotes(char *whitespace, char **line);
char		*get_token(char **line);
int			check_for_operator(char *array);
int			find_proper_allocation(char **array, int i);
int			len_to_token(char **array, int *flag);
char		*malloc_new_token(char **array);
char		**divide_into_arr(char **array, char **answer);
void		get_allocation_num(char *array, int *count);
void		*no_op(char **answer, char **array, int *offset, int *i);

#endif
