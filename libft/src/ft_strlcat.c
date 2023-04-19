/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:39:31 by tspoof            #+#    #+#             */
/*   Updated: 2022/11/05 13:54:54 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	if (i >= dstsize)
		return (ft_strlen(src) + dstsize);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	dst = dst + i;
	while (i < dstsize - 1 && *src != '\0' )
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
