/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:48:37 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/15 19:47:14 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

// Appends src memory to end of dst memory.
// Resizes the dst memory if needed.
int	vec_append(t_vec *dst, t_vec *src)
{
	size_t	alloc_size_min;
	int		ret;

	if (!dst || !src)
		return (-1);
	ret = 1;
	alloc_size_min = dst->len * dst->elem_size + src->len * src->elem_size;
	if (dst->alloc_size * 2 < alloc_size_min)
		ret = vec_resize(dst, dst->len + src->len);
	else if (dst->alloc_size < alloc_size_min)
		ret = vec_resize(dst, (dst->alloc_size / dst->elem_size) * 2);
	if (ret == -1)
		return (-1);
	ft_memcpy(&dst->memory[dst->elem_size * dst->len],
		src->memory,
		src->len * src->elem_size);
	dst->len = dst->len + src->len;
	return (1);
}
