/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:32:22 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/05 16:36:21 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"
#include "minishell.h"

// Expand utils
void	ft_tmp_to_result(char **result, char **tmp);
int		ft_should_expand_tilde(char *token, char *token_init);
char	*ft_var_end(char *str);
char	*ft_var_expand(t_vec env_vars, char *str);

// Env utils
char	*ft_getkey(char *str);
char	*ft_getvalue(char *str);
int		ft_env_update(t_env *envs, t_env env, int len);
char	*ft_env_to_str(t_env env);
void	free_envs(t_vec envs);
t_env	*ft_envfind(t_vec *envs_vec, char *key);

// Utils
int		ft_perror(char *error_msg);
int		is_builtin(char *cmd);

#endif
