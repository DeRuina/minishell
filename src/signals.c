/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:31:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/19 12:40:25 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	sig_ctrl_c(int signal)
{
	if (signal != SIGINT)
		return ;
	g_exit_status = 1;

	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_ctrl_c_exec(int signal)
{
	if (signal != SIGINT)
		return ;
	write(1, "\n", 1);
}
