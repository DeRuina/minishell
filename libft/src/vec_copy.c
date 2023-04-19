/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:22:29 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/23 18:56:29 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

int	vec_copy(t_vec *dst, t_vec *src)
{
	size_t	len_bytes;

	if (!dst || !src)
		return (-1);
	len_bytes = ft_min(dst->alloc_size, src->len * src->elem_size);
	ft_memcpy(dst->memory, src->memory, len_bytes);
	dst->len = len_bytes / dst->elem_size;
	return (1);
}
