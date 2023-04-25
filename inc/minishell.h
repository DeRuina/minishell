/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/25 11:51:36 by tspoof           ###   ########.fr       */
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

void	ft_env(void);
void	handle_quotes(char *whitespace, char **line);
char	*malloc_token(char *start, char *line);
char	*get_token(char **line);
char	**ft_cmd_trim(char *line);
void	ft_expand(char **line);

#endif
