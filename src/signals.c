/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:31:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/13 17:02:12 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	sig_ctrl_c(int signal)
{
	(void)signal; // should check if signal is correct?
	g_exit_status = 1;

	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
// void	sig_ctrl_bksl(int signal)
// {
// 	(void)signal;
// 	return ;
// }
