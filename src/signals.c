/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:31:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/22 15:22:52 by tspoof           ###   ########.fr       */
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
	g_exit_status = 130;
	write(1, "\n", 1);
}

void	sig_ctr_slash(int signal)
{
	if (signal != SIGQUIT)
		return ;
	g_exit_status = 131;
	write(1, "Quit: 3\n", 9);
}
