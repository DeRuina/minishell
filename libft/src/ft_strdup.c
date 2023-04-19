/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:50:57 by tspoof            #+#    #+#             */
/*   Updated: 2022/11/03 15:09:08 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	size;

	size = sizeof(char) * ft_strlen(s1) + 1;
	ptr = (char *)malloc(size);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, size);
	return (ptr);
}
