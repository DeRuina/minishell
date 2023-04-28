/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/28 14:57:57 by druina           ###   ########.fr       */
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

int			ft_putenv(t_vec *envs_vec, char *str);
char		*ft_getenv(t_vec envs_vec, char *key);
char		*ft_getkey(char *str);
char		*ft_getvalue(char *str);
int			quotes_cases(char first, char character, int *flag, char **line);
void		handle_quotes(char *whitespace, char **line);
char		*malloc_token(char *start, char *line);
char		*get_token(char **line);
char		**ft_cmd_trim(char *line);
void		ft_expand(char **line);
char		**ft_split_operators(char **array);
int			check_for_operator(char *array);
int			find_proper_allocation(char **array, int i);
int			len_to_token(char **array, int *flag);
char		*malloc_new_token(char **array);
char		**divide_into_arr(char **array, char **answer);

#endif
