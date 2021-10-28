/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:06:14 by j                 #+#    #+#             */
/*   Updated: 2021/10/28 23:07:50 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_n_format(char *line)
{
	size_t	nl_index;
	char	*leftovers;

	nl_index = 0;
	while (line[nl_index] != '\n' && line[nl_index] != '\0')
		nl_index++;
	if (line[nl_index] == '\0' || line[1] == '\0')
		return (NULL);
	leftovers = ft_substr(line, nl_index + 1, ft_strlen(line) - nl_index);
	if (*leftovers == '\0')
	{
		free(leftovers);
		leftovers = NULL;
	}
	line[nl_index + 1] = '\0';
	return (leftovers);
}

static char	read_n_append(int fd, char *buffer, char *leftovers)
{
	char	*temp;
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!leftovers)
			leftovers = ft_strdup("");
		temp = leftovers;
		leftovers = ft_strjoin(temp, buffer);
		free (temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (leftovers);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*leftovers;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_n_append(fd, buffer, leftovers);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	leftovers = update_n_format(line);
	return (line);
}
