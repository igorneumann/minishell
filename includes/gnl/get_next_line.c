/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narroyo- <narroyo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:46:10 by narroyo-          #+#    #+#             */
/*   Updated: 2021/03/14 13:23:48 by narroyo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr2(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

int	ft_output(int read_return, int fd, char **str, char **line)
{
	char	*tmp;

	tmp = str[fd];
	if (read_return == 0 && !str[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!ft_strchr2(str[fd], '\n'))
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	*line = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(ft_strchr2(tmp, '\n')));
	str[fd] = ft_strdup(ft_strchr2(tmp, '\n') + 1);
	free(tmp);
	return (1);
}

int	ft_read(int *read_return, int fd, char **line, char *buffer)
{
	*read_return = read(fd, buffer, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL || !buffer
		|| *read_return == -1)
	{
		free(buffer);
		return (-1);
	}
	return (*read_return);
}

int	get_next_line(int fd, char **line)
{
	int			read_return;
	char		*buffer;
	char		*tmp;
	static char	*str[4096];

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	read_return = ft_read(&read_return, fd, line, buffer);
	while (read_return > 0)
	{
		buffer[read_return] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strdup(str[fd]);
			free(str[fd]);
			str[fd] = ft_strjoin(tmp, buffer);
			free(tmp);
		}
		if (ft_strchr2(buffer, '\n'))
			break ;
		read_return = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (ft_output(read_return, fd, str, line));
}
