/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:54:42 by tspoof            #+#    #+#             */
/*   Updated: 2022/11/30 16:47:36 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_size(long num)
{
	int		i;

	i = 1;
	if (num < 0)
	{
		num = num * -1;
		i++;
	}
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static char	*ft_itoa_rec(long num, int sign, char *str)
{
	static int	i = 1;
	int			current_i;

	current_i = i;
	if (num >= 10)
	{
		i++;
		ft_itoa_rec(num / 10, sign, str);
	}
	if (num < 10)
	{
		if (sign == -1 && str)
		{
			str[0] = '-';
			i++;
		}
	}
	if (str)
		str[i - current_i] = num % 10 + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		sign;

	sign = 1;
	num = n;
	str = (char *)ft_calloc(ft_itoa_size(num) + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		num = num * -1;
		sign = -1;
	}
	str = ft_itoa_rec(num, sign, str);
	return (str);
}
