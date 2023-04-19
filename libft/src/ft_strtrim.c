/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:05:22 by tspoof            #+#    #+#             */
/*   Updated: 2022/11/09 18:58:39 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start_idx;
	size_t	end_idx;

	if (!s1 || !set)
		return (NULL);
	start_idx = 0;
	end_idx = ft_strlen(s1);
	while (ft_strchr(set, s1[start_idx]) && start_idx < end_idx)
		start_idx++;
	while (ft_strchr(set, s1[end_idx]) && start_idx < end_idx)
		end_idx--;
	ptr = ft_substr(s1 + start_idx, 0, end_idx - start_idx + 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}
