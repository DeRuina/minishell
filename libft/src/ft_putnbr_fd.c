/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:36:04 by tspoof            #+#    #+#             */
/*   Updated: 2022/11/29 14:57:03 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itofd(long num, int sign, int fd)
{
	if (num >= 10)
	{
		ft_itofd(num / 10, sign, fd);
	}
	if (num < 10)
	{
		if (sign == -1)
			ft_putchar_fd('-', fd);
	}
	ft_putchar_fd(num % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
		ft_itofd(num * -1, -1, fd);
	else
		ft_itofd(num, 1, fd);
}
