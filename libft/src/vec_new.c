/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:48:37 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/15 15:11:44 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

// Allocates init_len * elem_size bytes of memory to dst *memory.
int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || elem_size == 0)
		return (-1);
	dst->elem_size = elem_size;
	dst->alloc_size = elem_size * init_len;
	dst->len = 0;
	if (dst->alloc_size == 0)
		return (-1);
	dst->memory = malloc(dst->alloc_size);
	if (!dst->memory)
		return (-1);
	return (1);
}
