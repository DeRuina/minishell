/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:48 by druina            #+#    #+#             */
/*   Updated: 2023/05/08 15:56:33 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter)
{
	int		infile;
	char	*line;

	infile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (infile == -1)
		perror("here_doc file opening problem");
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (line == NULL)
			return (-1);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	// close(infile);
	// reopen_file_and_check(infile);
	return (infile);
}
