/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:48:26 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/23 18:23:30 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stdlib.h>
# include "libft.h"

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}	t_vec;
/**
 * @brief Appends memory to a vector.
 *
 * Appends *src memory to end of *dst memory.
 *
 * @param dst t_vec*
 * @param src t_vec*
 * @return int -1 if malloc fails otherwise 1
 */
int		vec_append(t_vec *dst, t_vec *src);
int		vec_copy(t_vec *dst, t_vec *src);
/**
 * @brief Frees vectors memory.
 *
 * Frees *memory and sets elem_size, alloc_size and len to 0.
 *
 * @param src t_vec
 */
void	vec_free(t_vec *src);
/**
 * @brief Creates a new vector from src.
 *
 * Allocates len * elem_size bytes of memory
 * and copies *src to it.
 *
 * @param dst t_vec*
 * @param src void*
 * @param init_len size_t
 * @param elem_size size_t
 * @return int -1 if malloc fails otherwise 1
 * @attention Allocates memory
 */
int		vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);
/**
 * @brief Creates a new vector.
 *
 * Allocates init_len * elem_size bytes of memory.
 *
 * @param dst t_vec*
 * @param init_len size_t
 * @param elem_size size_t
 * @return int -1 if malloc fails otherwise 1
 * @attention Allocates memory
 */
int		vec_new(t_vec *dst, size_t init_len, size_t elem_size);
/**
 * @brief Prepends memory to a vector.
 *
 * Prepends *src memory to the start of the *dst memory.
 *
 * @param dst t_vec*
 * @param src t_vec*
 * @return int -1 if malloc fails otherwise 1
 */
int		vec_prepend(t_vec *dst, t_vec *src);
/**
 * @brief Push element to the end of the vector.
 *
 * Takes in a vector and a pointer to an element
 * to be pushed to the end of the vector.
 *
 * @param dst t_vec*
 * @param src void*
 * @return int -1 if malloc fails otherwise 1
 */
int		vec_push(t_vec *dst, void *src);
/**
 * @brief Resizes vector.
 *
 * Creates a new srcs elem_size * target_len bytes sized vector and copies
 * srcs memory to it, frees the src memory and sets src to be the newly created
 * vector.
 *
 * @param src t_vec
 * @param target_len size_t length of the resized vector
 * @return int -1 if malloc fails otherwise 1
 */
int		vec_resize(t_vec *src, size_t target_len);

#endif
