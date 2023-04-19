/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:04:35 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/17 01:28:15 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_zerobuffer(char *buff)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buff[i] = '\0';
		i++;
	}
}

static int	gnl_read(int fd, char **fd_data)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*new_line;
	char	*tmp;
	size_t	size;

	new_line = NULL;
	while (!new_line)
	{
		new_line = ft_strchr(*fd_data, '\n');
		if (new_line)
			return (2);
		gnl_zerobuffer(buffer);
		size = read(fd, buffer, BUFFER_SIZE);
		if (!size)
			break ;
		tmp = ft_strjoin(*fd_data, buffer);
		if (!tmp)
			return (0);
		free(*fd_data);
		*fd_data = tmp;
	}
	return (1);
}

static char	*gnl_get_line(char **fd_data)
{
	char	*line;
	char	*tmp;
	size_t	i;

	tmp = ft_strchr(*fd_data, '\n');
	i = (size_t)(tmp - *fd_data) + 1;
	line = ft_substr(*fd_data, 0, i);
	tmp = ft_substr(*fd_data, i, ft_strlen(*fd_data));
	if (!tmp || !line)
		return (NULL);
	free(*fd_data);
	*fd_data = tmp;
	return (line);
}

static char	*gnl_line(int read_return, char **fd_data)
{
	char	*line;

	if (read_return == 1)
	{
		if (!fd_data || !*fd_data)
			return (NULL);
		if (*fd_data[0])
		{
			line = ft_substr(*fd_data, 0, ft_strlen(*fd_data));
			free(*fd_data);
			*fd_data = NULL;
			if (!line)
				return (NULL);
			return (line);
		}
		free(*fd_data);
		*fd_data = NULL;
		return (NULL);
	}
	line = gnl_get_line(fd_data);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*fd_list[1024] = {0};
	char		*line;
	int			read_return;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!fd_list[fd])
	{
		fd_list[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!fd_list[fd])
			return (NULL);
		fd_list[fd][0] = '\0';
	}
	if (!fd_list[fd])
		return (NULL);
	read_return = gnl_read(fd, &fd_list[fd]);
	if (!read_return)
	{
		free(fd_list[fd]);
		return (NULL);
	}
	line = gnl_line(read_return, &fd_list[fd]);
	return (line);
}
