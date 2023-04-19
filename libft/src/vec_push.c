/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:48:37 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/15 15:11:55 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

// Takes in a vector and a pointer to an element
// to be pushed to the end of the vector.
int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !src)
		return (-1);
	if (dst->len * dst->elem_size + dst->elem_size > dst->alloc_size)
		if (!vec_resize(dst, dst->len * 2))
			return (-1);
	ft_memcpy(&dst->memory[dst->len * dst->elem_size], src, dst->elem_size);
	dst->len++;
	return (1);
}
