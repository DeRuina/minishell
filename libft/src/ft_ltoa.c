/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:54:42 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/09 16:16:25 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_count(unsigned long n)
{
	int		i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_ltostr(int sign, unsigned long len, unsigned long n, char *str)
{
	while (len)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

char	*ft_ltoa(long n)
{
	char			*result;
	int				sign;
	unsigned long	num;
	unsigned int	len;

	sign = 1;
	len = 0;
	if (n < 0)
	{
		sign = -1;
		num = n * -1;
		len++;
	}
	else
		num = n;
	len = len + ft_char_count(num);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	result = ft_ltostr(sign, len, num, result);
	return (result);
}
