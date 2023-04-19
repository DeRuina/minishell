/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:04:38 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/17 01:28:02 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/**
 * @brief Gets next line from a file.
 *
 * Everytime the function is called it returns the next line from a file.
 * Works with multiple files.
 * @param fd File descriptor
 * @returns String or NULL if there is no more lines in the file
 * @attention Allocates memory
 */
char	*get_next_line(int fd);

#endif
