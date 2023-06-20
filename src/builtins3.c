/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:01:07 by druina            #+#    #+#             */
/*   Updated: 2023/06/20 15:02:08 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// closing and reopening file for truncing it

static void	trunc_file_if_needed(char *filename, int *outfile)
{
	if (filename)
	{
		close ((*outfile));
		(*outfile) =  open(filename, O_CREAT | O_RDWR | O_TRUNC, 0664);
		if ((*outfile) == -1)
			perror(filename);
	}
}

// If echo no args

static int	is_command(char *cmd, int outfile)
{
	if (!cmd)
	{
		write(outfile, "\n", 1);
		return (0);
	}
	return(1);
}

// Prints the arguments on the screen

void	ft_echo(char **full_cmd, int outfile, char *filename)
{
	int	i;
	int	flag_n;

	i = 1;
	flag_n = 0;
	trunc_file_if_needed(filename, &outfile);
	if (!is_command(full_cmd[1], outfile))
		return ;
	if (ft_strncmp(full_cmd[1], "-n", 2) == 0 && ft_strlen(full_cmd[1]) == 2
		&& i++)
		flag_n = 1;
	while (1)
	{
		if (full_cmd[i] && *full_cmd[i] != '\0')
			write(outfile, full_cmd[i], ft_strlen(full_cmd[i]));
		i++;
		if (full_cmd[i] == 0)
			break ;
		if (*full_cmd[i] != '\0')
			write(outfile, " ", 1);
	}
	if (flag_n != 1)
		write(outfile, "\n", 1);
}
