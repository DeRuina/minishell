/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:03:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/23 19:21:36 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	case_only_redirections(char ***array)
{
	while (*(*array) && **(*array) != '|' && **(*array) != '\0')
		(*array)++;
	if (*(*array))
		(*array)++;
}

int	cmd_len(char **array)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (array[i] && ft_strncmp(array[i], "|", 1) != 0)
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

char	**get_node_cmd(char ***array)
{
	char	**answer;
	int		i;

	i = 0;
	if (cmd_len(*array) == 0)
		return (case_only_redirections(array), NULL);
	answer = (char **)malloc(sizeof(char *) * (cmd_len(*array) + 1));
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

t_node	*new_node(char ***array, int *error_flag, t_vec env)
{
	t_node	*node;
	char		*temp;

	if (array == NULL)
		return (NULL);
	node = (t_node *)ft_calloc(1 ,sizeof(t_node));
	if (!node)
		return (NULL);
	node = ft_fd_handler((*array), error_flag, node);
	node->full_cmd = get_node_cmd(array);
	if (node->full_cmd != NULL)
	{
		temp = node->full_cmd[0];
		node->full_cmd[0] = ft_get_exec_path(env, node->full_cmd[0]);
		if (temp)
			free(temp);
	}
	if (!**array)
		node->next = NULL;
	else
		node->next = new_node(array, error_flag, env);
	return (node);
}

t_node	*ft_parse_args(char *line, t_vec env, int **pipe_nbr)
{
	t_node		*head;
	char		**tokens;
	char		**temp;
	
	static int	error_flag = 0;


	tokens = ft_cmd_trim(line);
	if (!tokens)
		exit(EXIT_FAILURE);
	ft_expand(env, tokens);
	tokens = ft_split_operators(tokens);
	tokens = ft_str_trim(tokens);
	temp = tokens;
	head = new_node(&tokens, &error_flag, env);
	// free_2d(temp);
	return (head);
}
