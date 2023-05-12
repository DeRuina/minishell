/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:03:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/12 16:18:47 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_node_cmd(char **array)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (array[i] && ft_strncmp(array[i], "|", 1) != 0 && array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<", 1) == 0 || ft_strncmp(array[i], ">",
				1) == 0)
			i += 2;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	case_only_redirections(char ***array)
{
	while (*(*array) && **(*array) != '|' && **(*array) != '\0')
		(*array)++;
	if (*(*array))
		(*array)++;
}

char	**get_node_cmd(char ***array)
{
	char	**answer;
	int		i;

	i = 0;
	if (len_node_cmd(*array) == 0)
		return (case_only_redirections(array), NULL);
	answer = (char **)malloc(sizeof(char *) * len_node_cmd(*array) + 1);
	if (!answer)
		return (NULL);
	while (*(*array) && **(*array) != '|' && **(*array) != '\0')
	{
		if (ft_strncmp(*(*array), "<", 1) == 0 || ft_strncmp(*(*array), ">",
				1) == 0)
			(*array) += 2;
		else
		{
			answer[i++] = *(*array);
			(*array)++;
		}
	}
	if (*(*array))
		(*array)++;
	answer[i] = 0;
	return (answer);
}

t_node	*new_node_and_link(char ***array, int *flag)
{
	t_node	*node;
	int		*fds;

	if (array == NULL)
		return (NULL);
	node = (t_node *)malloc(sizeof(t_node) * 1);
	if (!node)
		return (NULL);
	fds = ft_fd_handler((*array), flag);
	if (fds != NULL)
	{
		node->infile = fds[0];
		node->outfile = fds[1];
	}
	node->full_cmd = get_node_cmd(array);
	if (node->full_cmd == NULL)
		node->path_name = NULL;
	else
		node->path_name = node->full_cmd[0];
	if (!**array)
		node->next_node = NULL;
	else
		node->next_node = new_node_and_link(array, flag);
	return (node);
}

t_node	*ft_parse_args(char **array)
{
	t_node		*head;
	static int	flag = 0;

	head = new_node_and_link(&array, &flag);
	return (head);
}
