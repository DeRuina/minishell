/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/24 08:49:40 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

void	handle_quotes(char *whitespace, char **line);
char	*get_token(char **line);
char	**ft_cmd_trim(char *line);

#endif
