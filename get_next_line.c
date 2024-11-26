/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:38:12 by yrafai            #+#    #+#             */
/*   Updated: 2024/11/24 14:25:59 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *remainder)
{
	size_t	len;
	char	*line;

	len = 0;
	while (remainder[len] && remainder[len] != '\n')
		len++;
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	len = 0;
	while (remainder[len] && remainder[len] != '\n')
	{
		line[len] = remainder[len];
		len++;
	}
	if (remainder[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

static char	*update_remainder(char **remainder, char **buffer, char *line)
{
	size_t	start;
	size_t	i;
	char	*new_remainder;

	start = ft_strlen(line);
	i = 0;
	clean(buffer);
	if (!line || !(*remainder)[start])
		return (clean(remainder));
	new_remainder = malloc(ft_strlen(*remainder) - start + 1);
	if (!new_remainder)
		return (clean(remainder));
	while ((*remainder)[start])
		new_remainder[i++] = (*remainder)[start++];
	new_remainder[i] = '\0';
	clean(remainder);
	return (new_remainder);
}

static void	append_buffer(char **remainder, char *buffer, ssize_t bytes)
{
	char	*tmp;

	buffer[bytes] = '\0';
	tmp = ft_strjoin(*remainder, buffer);
	clean(remainder);
	*remainder = tmp;
}

static char	*finalize(ssize_t bytes, char **remainder, char **buffer)
{
	char	*result;

	if (bytes == 0 && *remainder && **remainder)
	{
		result = ft_strdup(*remainder);
		clean(remainder);
		clean(buffer);
		return (result);
	}
	clean(remainder);
	clean(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (clean(&remainder));
	while (1)
	{
		if (remainder && ft_strchr(remainder, '\n'))
		{
			line = extract_line(remainder);
			remainder = update_remainder(&remainder, &buffer, line);
			return (line);
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (finalize(bytes, &remainder, &buffer));
		append_buffer(&remainder, buffer, bytes);
	}
}
