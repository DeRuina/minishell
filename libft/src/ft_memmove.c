/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:15:29 by tspoof            #+#    #+#             */
/*   Updated: 2022/11/30 17:07:04 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst != src)
	{
		if (src < dst)
		{
			while (len > 0)
			{
				*((char *)(dst + len - 1)) = *((char *)(src + len - 1));
				len--;
			}
		}
		else
		{
			i = 0;
			while (i < len)
			{
				*((char *)(dst + i)) = *((char *)(src + i));
				i++;
			}
		}
	}
	return (dst);
}
