/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:22 by druina            #+#    #+#             */
/*   Updated: 2023/05/18 12:07:15 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// finds and mallocs the next token

char	*malloc_new_token_and_move_pointer_to_next(char **array)
{
	int		i;
	char	*answer;
	char	*temp;
	int		len;

	temp = (*array);
	i = 0;
	len = pointer_to_next_token_return_len(array);
	answer = (char *)malloc(sizeof(char) * len + 1);
	if (!answer)
		return (NULL);
	while (i < len)
	{
		answer[i] = temp[i];
		i++;
	}
	answer[i] = '\0';
	return (answer);
}

//	returns malloced token that has no operator combined

char	*no_operator(char *array)
{
	char	*answer;
	int		j;

	j = 0;
	answer = (char *)malloc(sizeof(char) * (ft_strlen(array) + 1));
	while (array[j] != '\0')
	{
		answer[j] = array[j];
		j++;
	}
	answer[j] = '\0';
	return (answer);
}
