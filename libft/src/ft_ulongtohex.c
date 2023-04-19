/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulongtohex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:20:01 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/08 17:22:22 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex_char_count(unsigned long n)
{
	int		i;

	i = 1;
	while (n >= 16)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static char	ft_decimal16_to_hex(int dec)
{
	if (dec < 10)
		return (dec + '0');
	if (dec == 10)
		return ('a');
	if (dec == 11)
		return ('b');
	if (dec == 12)
		return ('c');
	if (dec == 13)
		return ('d');
	if (dec == 14)
		return ('e');
	if (dec == 15)
		return ('f');
	return (0);
}

char	*ft_ulongtohex(unsigned long n)
{
	char	*str;
	int		len;
	int		hex;

	len = ft_hex_char_count(n);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (len)
	{
		hex = ft_decimal16_to_hex(n % 16);
		str[len - 1] = hex;
		n = n / 16;
		len--;
	}
	return (str);
}
