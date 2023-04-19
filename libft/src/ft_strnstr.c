/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:17:40 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/08 00:53:31 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// First checks if needles first char matches with a char in haystack.
// Then compares needles and haystacks characters one by one
// from that point froward.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		needle_len;

	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	i = 0;
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j]
				&& i + j < len)
				j++;
			if (j == needle_len)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
