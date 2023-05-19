/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:32:22 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/17 19:57:55 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"

// Expand utils
void			ft_tmp_to_result(char **result, char **tmp);
int				ft_should_expand_tilde(char *token, char *token_init);
char			*ft_var_end(char *str);
char			*ft_var_expand(t_vec env_vars, char *str);

#endif
