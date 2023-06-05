/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:59:13 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/05 14:29:45 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_remove(t_vec *src, size_t index)
{
	unsigned char	*start;

	start = src->memory + (index * src->elem_size);
	start = ft_memmove(start,
			start + src->elem_size,
			(src->len - index - 1) * src->elem_size);
	src->len--;
	return (0);
}
