/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:03:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/10 12:47:30 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_node_cmd(char **array)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (array[i] && ft_strncmp(array[i], "|", 1) != 0 && ft_strncmp(array[i], "'\0", 1) != 0)
	{
		if (ft_strncmp(array[i], "<", 1) == 0 || ft_strncmp(array[i], ">", 1) == 0)
			i += 2;
		else
		{
			len++;
			i++;
		}
	}
	return(len);
}

char **get_node_cmd(char ***array)
{
	char **answer;
	int i;
	int len;

	i = 0;
	len = len_node_cmd((*array));
	if (len == 0)
		return(NULL);
	answer = (char **)malloc(sizeof(char *) * len + 1);
	if (!answer)
		return(NULL);
	while (**(*array) != '|' && **(*array) != '\0')
	{
		if (ft_strncmp(*(*array), "<", 1) == 0 || ft_strncmp(*(*array), ">", 1) == 0)
			(*array) += 2;
		else
		{
			answer[i++] = *(*array);
			(*array)++;
		}
	}
	answer[i] = 0;
	return (answer);
}

t_node *new_node(char ***array)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node) * 1);
	if (!node)
		return (NULL);
	node->full_cmd = get_node_cmd(array);
	if (node->full_cmd == NULL)
		node->path_name = NULL;
	else
		node->path_name = node->full_cmd[0];
	if (!array)
	node->next_node = NULL;
	else
		node->next_node = new_node(array);


	return(node);
}

// t_node	*ft_parse_args(char *line)
// {
// 	t_node *node;


// 	return(node);
// }
